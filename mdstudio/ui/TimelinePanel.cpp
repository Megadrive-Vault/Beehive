///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2016 Matt Phillips, Big Evil Corporation
// http://www.bigevilcorporation.co.uk
// mattphillips@mail.com
// @big_evil_corp
//
// Licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.html
///////////////////////////////////////////////////////

#include "TimelinePanel.h"
#include "MainWindow.h"

#include <ion/core/time/Time.h>

#include <wx/menu.h>

#include <sstream>

const char* TimelinePanel::s_trackNames[eTrackCount] =
{
	"Position",
	"Sprite Anim"
};

TimelinePanel::TimelinePanel(MainWindow& mainWindow, Project& project, ion::render::Renderer& renderer, wxGLContext& glContext, RenderResources& renderResources, wxWindow *parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: TimelinePanelBase(parent, winid, pos, size, style)
	, m_mainWindow(mainWindow)
	, m_project(project)
	, m_timer(this)
{
	m_animationId = InvalidAnimationId;
	m_animation = NULL;
	m_actorId = InvalidActorId;
	m_actor = NULL;
	m_prevClock = 0;

	PopulateAnimations();

	m_gridTimeline->DeleteRows(0, m_gridTimeline->GetNumberRows());
	m_gridTimeline->DeleteCols(0, m_gridTimeline->GetNumberCols());

	Bind(wxEVT_TIMER, &TimelinePanel::EventHandlerTimer, this, m_timer.GetId());
	Bind(wxEVT_SIZE, &TimelinePanel::OnResize, this, GetId());

	m_timer.Start(1);
}

TimelinePanel::~TimelinePanel()
{

}

void TimelinePanel::EventHandlerTimer(wxTimerEvent& event)
{
	if(m_animation && m_animation->GetState() == ion::render::Animation::ePlaying)
	{
		//Get accurate delta
		u64 clock = ion::time::GetSystemTicks();
		u64 diff = clock - m_prevClock;
		m_prevClock = clock;
		float delta = ion::time::TicksToSeconds(diff);

		m_animation->Update(delta);
		float time = m_animation->GetFrame();
		SetSliderFrame(time);
		m_gridTimeline->GoToCell(0, ion::maths::Floor(time));

		if(m_toolIsolateObject->IsToggled() && m_actor)
		{
			SyncActor(*m_actor);
		}
		else
		{
			SyncAllActors();
		}
	}
}

void TimelinePanel::SetSliderFrame(float frame)
{
	float lerpTime = ion::maths::UnLerp(0.0f, m_animation->GetLength(), frame);
	m_sliderTimeline->SetValue((int)ion::maths::Round(lerpTime * 100.0f));
}

void TimelinePanel::PopulateAnimations()
{
	m_choiceAnims->Clear();
	m_animCache.clear();

	typedef std::pair<std::string, AnimationId> TNameIDPair;
	typedef std::vector<TNameIDPair> TNameList;
	TNameList nameList;

	for(TAnimationMap::const_iterator it = m_project.AnimationsBegin(), end = m_project.AnimationsEnd(); it != end; ++it)
	{
		nameList.push_back(std::make_pair(it->second.GetName(), it->first));
	}

	std::sort(nameList.begin(), nameList.end(), [](TNameIDPair& a, TNameIDPair& b) { return a.first < b.first; });

	for(int i = 0; i < nameList.size(); i++)
	{
		//Store by index
		m_animCache.push_back(nameList[i].second);

		//Add to list
		m_choiceAnims->AppendString(nameList[i].first);
	}
}

void TimelinePanel::PopulateTimeline(const Animation& animation, const AnimationActor* actor)
{
	//Clear existing
	m_gridTimeline->DeleteRows(0, m_gridTimeline->GetNumberRows());
	m_gridTimeline->DeleteCols(0, m_gridTimeline->GetNumberCols());

	//Set drop-down
	std::vector<AnimationId>::iterator it = std::find_if(m_animCache.begin(), m_animCache.end(), [&](const AnimationId& animId) { return animId == animation.GetId(); });
	int index = std::distance(it, m_animCache.begin());

	if(m_choiceAnims->GetSelection() != index)
	{
		m_choiceAnims->SetSelection(index);
	}

	if(actor)
	{
		//Populate keyframes from selected actor
		int numKeyframes = actor->m_trackPosition.GetNumKeyframes();

		//Create all columns
		m_gridTimeline->AppendCols(numKeyframes);

		//Set column labels
		for(int i = 0; i < numKeyframes; i++)
		{
			std::stringstream label;
			label << actor->m_trackPosition.GetKeyframe(i).GetTime();
			m_gridTimeline->SetColLabelValue(i, label.str());
		}

		//Create all rows
		m_gridTimeline->AppendRows(eTrackCount + 1);

		//Set row labels
		m_gridTimeline->SetRowLabelValue(0, "Keyframe Length");
		for(int i = 0; i < eTrackCount; i++)
		{
			m_gridTimeline->SetRowLabelValue(i + 1, s_trackNames[i]);
		}

		//Set column labels
		for(int i = 0; i < numKeyframes; i++)
		{
			std::stringstream label;
			label << i;
			m_gridTimeline->SetColLabelValue(i, label.str());
		}

		if(GameObject* gameObject = m_project.GetEditingMap().GetGameObject(actor->GetGameObjectId()))
		{
			if(const GameObjectType* gameObjectType = m_project.GetGameObjectType(gameObject->GetTypeId()))
			{
				//Populate keyframe length track
				for(int i = 0; i < numKeyframes; i++)
				{
					float currTime = actor->m_trackPosition.GetKeyframe(i).GetTime();
					float nextTime = 0.0f;

					if(i < numKeyframes-1)
					{
						nextTime = actor->m_trackPosition.GetKeyframe(i + 1).GetTime();
					}
					else
					{
						nextTime = m_animation->GetLength();
					}

					float length = (nextTime - currTime);

					std::stringstream label;
					label << length;
					m_gridTimeline->SetCellValue(label.str(), 0, i);

					//Set column width
					int colWidth = (int)(length * (float)m_gridTimeline->GetDefaultColSize());
					m_gridTimeline->SetColumnWidth(i, colWidth);
				}

				//Populate position track
				for(int i = 0; i < numKeyframes; i++)
				{
					std::stringstream label;
					ion::Vector2i value = actor->m_trackPosition.GetKeyframe(i).GetValue();
					label << "(" << value.x << "," << value.y << ")";
					m_gridTimeline->SetCellValue(label.str(), eTrackPosition + 1, i);
				}

				//Populate sprite anim track
				for(int i = 0; i < numKeyframes; i++)
				{
					std::stringstream label;
					std::pair<SpriteSheetId, SpriteAnimId> value = actor->m_trackSpriteAnim.GetKeyframe(i).GetValue();
					if(Actor* spriteActor = m_project.GetActor(gameObjectType->GetSpriteActorId()))
					{
						if(SpriteSheet* spriteSheet = spriteActor->GetSpriteSheet(value.first))
						{
							if(SpriteAnimation* spriteAnim = spriteSheet->GetAnimation(value.second))
							{
								std::stringstream label;
								label << spriteSheet->GetName() << ":" << spriteAnim->GetName();
								m_gridTimeline->SetCellValue(label.str(), eTrackSpriteAnim + 1, i);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		//Populate frames from selected animation
		int numFrames = ion::maths::Ceil(animation.GetLength());

		//Create all columns
		m_gridTimeline->AppendCols(numFrames);

		//Set column labels
		for(int i = 0; i < numFrames; i++)
		{
			std::stringstream label;
			label << (float)i;
			m_gridTimeline->SetColLabelValue(i, label.str());
		}

		//Create all rows
		m_gridTimeline->AppendRows(eTrackCount + 1);

		//Set row labels
		for(int i = 0; i < eTrackCount; i++)
		{
			m_gridTimeline->SetRowLabelValue(i + 1, s_trackNames[i]);
		}

		//Set game object label
		m_textCurrentActor->SetLabel("[All objects]");
	}

	BuildGridColPosCache();
}

void TimelinePanel::SetCurrentActor(GameObjectId actorId)
{
	if(actorId != m_actorId)
	{
		if(const GameObject* gameObject = m_project.GetEditingMap().GetGameObject(actorId))
		{
			m_actorId = actorId;

			if(m_animation)
			{
				m_actor = m_animation->GetActor(actorId);

				if(m_actor)
				{
					//Populate timeline
					PopulateTimeline(*m_animation, m_actor);

					//Set game object label
					std::stringstream label;

					std::string objName = gameObject->GetName();
					if(objName.empty())
					{
						objName = "<No Name>";
					}

					label << objName << " (object " << gameObject->GetId() << ")";
					m_textCurrentActor->SetLabel(label.str());

					//Populate sprite actor choices
					m_choiceSpriteAnim->Clear();
					m_spriteSheetCache.clear();

					if(const GameObjectType* gameObjectType = m_project.GetGameObjectType(gameObject->GetTypeId()))
					{
						ActorId spriteActorId = gameObjectType->GetSpriteActorId();
						if(Actor* spriteActor = m_project.GetActor(spriteActorId))
						{
							for(TSpriteSheetMap::iterator spriteSheetIt = spriteActor->SpriteSheetsBegin(), spriteSheetEnd = spriteActor->SpriteSheetsEnd(); spriteSheetIt != spriteSheetEnd; ++spriteSheetIt)
							{
								for(TSpriteAnimMap::iterator animIt = spriteSheetIt->second.AnimationsBegin(), animEnd = spriteSheetIt->second.AnimationsEnd(); animIt != animEnd; ++animIt)
								{
									std::stringstream label;
									label << spriteSheetIt->second.GetName() << ":" << animIt->second.GetName();
									m_choiceSpriteAnim->AppendString(label.str());
									m_spriteSheetCache.push_back(std::make_pair(spriteSheetIt->first, animIt->first));
								}
							}
						}
					}
				}
			}
		}
	}
}

AnimationId TimelinePanel::GetCurrentAnimation() const
{
	return m_animationId;
}

void TimelinePanel::SyncActor(AnimationActor& actor)
{
	if(m_animation)
	{
		if(GameObject* gameObject = m_project.GetEditingMap().GetGameObject(actor.GetGameObjectId()))
		{
			float frame = m_animation->GetFrame();
			SpriteAnimId originalSpriteAnim = gameObject->GetSpriteAnim();

			//Get all track values
			ion::Vector2i position = actor.m_trackPosition.GetValue(frame);
			std::pair<SpriteSheetId, SpriteAnimId> spriteAnim = actor.m_trackSpriteAnim.GetValue(frame);

			//Apply to game object
			m_project.GetEditingMap().MoveGameObject(actor.GetGameObjectId(), position.x, position.y);
			gameObject->SetPosition(position);
			gameObject->SetSpriteSheetId(spriteAnim.first);
			gameObject->SetSpriteAnim(spriteAnim.second);

			//Advance current sprite anim
			if(const GameObjectType* gameObjectType = m_project.GetGameObjectType(gameObject->GetTypeId()))
			{
				if(Actor* spriteActor = m_project.GetActor(gameObjectType->GetSpriteActorId()))
				{
					if(SpriteSheet* spriteSheet = spriteActor->GetSpriteSheet(spriteAnim.first))
					{
						if(SpriteAnimation* spriteAnimation = spriteSheet->GetAnimation(spriteAnim.second))
						{
							float spriteAnimStartTime = m_actor->m_trackSpriteAnim.GetPrevKeyframe(frame)->GetTime();
							float spriteAnimFrame = (frame - spriteAnimStartTime) * spriteAnimation->GetPlaybackSpeed();
							float spriteAnimLength = spriteAnimation->GetLength();

							if(spriteAnimation->GetPlaybackBehaviour() == ion::render::Animation::eLoop)
							{
								spriteAnimation->SetFrame(ion::maths::Fmod(spriteAnimFrame, spriteAnimLength));
							}
							else
							{
								spriteAnimation->SetFrame(ion::maths::Clamp(spriteAnimFrame, 0.0f, spriteAnimLength));
							}
						}
					}
				}
			}

			//Refresh map panel
			m_mainWindow.RedrawPanel(MainWindow::ePanelMap);
		}
	}
}

void TimelinePanel::SyncAllActors()
{
	if(m_animation)
	{
		for(TAnimActorMap::iterator it = m_animation->ActorsBegin(), end = m_animation->ActorsEnd(); it != end; ++it)
		{
			SyncActor(it->second);
		}
	}
}

void TimelinePanel::Refresh(bool eraseBackground, const wxRect *rect)
{
	if(!m_mainWindow.IsRefreshLocked())
	{
	}
}

void TimelinePanel::OnSpinSpeed(wxSpinEvent& event)
{
	if(m_animation)
	{
		m_animation->SetPlaybackSpeed((float)m_spinSpeed->GetValue());
	}
}

void TimelinePanel::OnSelectAnimation(wxCommandEvent& event)
{
	int index = event.GetSelection();
	m_animationId = m_animCache[index];
	m_animation = m_project.GetAnimation(m_animationId);
	if(m_animation)
	{
		m_animation->SetState(ion::render::Animation::eStopped);
		PopulateTimeline(*m_animation, NULL);
	}
}

void TimelinePanel::OnSelectSpriteAnim(wxCommandEvent& event)
{
	if(m_animation && m_actor)
	{
		if(GameObject* gameObject = m_project.GetEditingMap().GetGameObject(m_actor->GetGameObjectId()))
		{
			gameObject->SetSpriteSheetId(m_spriteSheetCache[m_choiceSpriteAnim->GetSelection()].first);
			gameObject->SetSpriteAnim(m_spriteSheetCache[m_choiceSpriteAnim->GetSelection()].second);

			PopulateTimeline(*m_animation, m_actor);
			m_mainWindow.RedrawPanel(MainWindow::ePanelMap);
		}
	}
}

void TimelinePanel::OnToolAddAnim(wxCommandEvent& event)
{
	DialogNewAnim dialog(this);

	if(dialog.ShowModal() == wxID_OK)
	{
		m_animationId = m_project.CreateAnimation();
		m_animation = m_project.GetAnimation(m_animationId);
		m_animation->SetName(dialog.m_textName->GetValue().GetData().AsChar());
		PopulateAnimations();
		PopulateTimeline(*m_animation, NULL);
	}
}

void TimelinePanel::OnToolDeleteAnim(wxCommandEvent& event)
{
	if(m_animation)
	{
		m_gridTimeline->DeleteRows(0, m_gridTimeline->GetNumberRows());
		m_gridTimeline->DeleteCols(0, m_gridTimeline->GetNumberCols());

		m_project.DeleteAnimation(m_animationId);
		m_animationId = InvalidAnimationId;
		m_animation = NULL;
		m_actorId = InvalidActorId;

		PopulateAnimations();
	}
}

namespace
{
	template <typename T> void AddOrEditKeyframe(const T& value, ion::render::AnimationTrack<T>& track, float frame)
	{
		if(ion::render::Keyframe<T>* keyframe = track.FindKeyframe(frame))
		{
			keyframe->SetValue(value);
		}
		else
		{
			track.InsertKeyframe(ion::render::Keyframe<T>(frame, value));
		}
	}

	void KeyframeObjectCurrentState(Project& project, AnimationActor& actor, float frame)
	{
		if(GameObject* gameObject = project.GetEditingMap().GetGameObject(actor.GetGameObjectId()))
		{
			//Add/edit keyframes for all tracks
			AddOrEditKeyframe(gameObject->GetPosition(), actor.m_trackPosition, frame);
			AddOrEditKeyframe(std::make_pair(gameObject->GetSpriteSheetId(), gameObject->GetSpriteAnim()), actor.m_trackSpriteAnim, frame);
		}
	}
}

void TimelinePanel::Keyframe(AnimationActor* actor)
{
	if(m_animation)
	{
		//Get current frame
		float frame = m_animation->GetFrame();

		if(actor)
		{
			//Edit or insert keyframe for current actor
			KeyframeObjectCurrentState(m_project, *actor, frame);
		}
		else
		{
			//Edit or insert keyframe for all actors
			for(TAnimActorMap::iterator it = m_animation->ActorsBegin(), end = m_animation->ActorsEnd(); it != end; ++it)
			{
				KeyframeObjectCurrentState(m_project, it->second, frame);
			}
		}

		//If at end, advance to next keyframe
		if(frame >= m_animation->GetLength() - 1.0f)
		{
			//Advance frame
			frame += 1.0f;

			//Set next frame
			m_animation->SetFrame(frame);

			//Update sider
			SetSliderFrame(frame);
		}

		//Adjust anim length
		SetAnimLength(*m_animation, *actor);

		if(m_toolIsolateObject->IsToggled() && actor)
		{
			SyncActor(*actor);
		}
		else
		{
			SyncAllActors();
		}

		//Redraw map panel
		m_mainWindow.RedrawPanel(MainWindow::ePanelMap);

		//Populate timeline
		PopulateTimeline(*m_animation, m_actor);
	}
}

void TimelinePanel::SetAnimLength(Animation& animation, const AnimationActor& actor)
{
	float length = 1.0f;

	for(int i = 0; i < actor.m_trackPosition.GetNumKeyframes(); i++)
	{
		length += actor.m_trackPosition.GetKeyframe(i).GetTime();
	}

	animation.SetLength(length);
}

void TimelinePanel::BuildGridColPosCache()
{
	m_gridColPosCache.clear();
	m_gridColPosCache.reserve(m_gridTimeline->GetNumberCols());

	for(int i = 0; i < m_gridTimeline->GetNumberCols(); i++)
	{
		m_gridColPosCache.push_back(m_gridTimeline->GetColumnWidth(i));
	}
}

void TimelinePanel::OnToolKeyframeActor(wxCommandEvent& event)
{
	if(m_actor)
	{
		Keyframe(m_actor);
	}
}

void TimelinePanel::OnToolKeyframeAll(wxCommandEvent& event)
{
	Keyframe(NULL);
}

void TimelinePanel::OnToolPlay(wxCommandEvent& event)
{
	if(m_animation)
	{
		m_animation->SetState(ion::render::Animation::ePlaying);
	}
}

void TimelinePanel::OnToolStop(wxCommandEvent& event)
{
	if(m_animation)
	{
		m_animation->SetState(ion::render::Animation::eStopped);
	}
}

void TimelinePanel::OnToolRewind(wxCommandEvent& event)
{
	if(m_animation)
	{
		m_animation->SetFrame(0.0f);
	}

	SetSliderFrame(0.0f);

	if(m_toolIsolateObject->IsToggled() && m_actor)
	{
		SyncActor(*m_actor);
	}
	else
	{
		SyncAllActors();
	}

	m_mainWindow.RedrawPanel(MainWindow::ePanelMap);
}

void TimelinePanel::OnToolIsolateObject(wxCommandEvent& event)
{
	if(event.IsChecked() && !m_actor)
	{
		m_toolIsolateObject->SetToggle(false);
	}
}

void TimelinePanel::OnSliderTimelineChange(wxScrollEvent& event)
{
	if(m_animation)
	{
		float time = ion::maths::Lerp(0.0f, m_animation->GetLength(), (float)m_sliderTimeline->GetValue() / 100.0f);
		m_animation->SetFrame(time);
		
		std::stringstream frameText;
		frameText << "Frame: " << time;
		m_textFrame->SetLabel(frameText.str());

		if(m_toolIsolateObject->IsToggled() && m_actor)
		{
			SyncActor(*m_actor);
		}
		else
		{
			SyncAllActors();
		}
		
		m_mainWindow.RedrawPanel(MainWindow::ePanelMap);
	}
}

void TimelinePanel::OnTimelineColResize(wxGridSizeEvent& event)
{
	TimelinePanelBase::OnTimelineColResize(event);

	if(m_animation && m_actor)
	{
		int column = event.GetRowOrCol();
		int keyframe = column;

		if(keyframe < m_actor->m_trackPosition.GetNumKeyframes() - 1)
		{
			int prevWidthPixels = m_gridColPosCache[column];
			int newWidthPixels = m_gridTimeline->GetColumnWidth(column);
			float currentTime = m_actor->m_trackPosition.GetKeyframe(keyframe + 1).GetTime();
			float delta = ((float)newWidthPixels - (float)prevWidthPixels) / (float)m_gridTimeline->GetDefaultColSize();

			const float minTime = 0.01f;

			if((currentTime + delta) < minTime)
			{
				delta = currentTime = minTime;
			}

			//Shift all keyframes beyond current
			for(int i = keyframe + 1; i < m_actor->m_trackPosition.GetNumKeyframes(); i++)
			{
				m_actor->m_trackPosition.GetKeyframe(i).SetTime(m_actor->m_trackPosition.GetKeyframe(i).GetTime() + delta);
				m_actor->m_trackSpriteAnim.GetKeyframe(i).SetTime(m_actor->m_trackSpriteAnim.GetKeyframe(i).GetTime() + delta);
			}

			//Adjust anim length
			SetAnimLength(*m_animation, *m_actor);

			//Redraw
			PopulateTimeline(*m_animation, m_actor);

			m_gridTimeline->SetColumnWidth(column, newWidthPixels);
			Refresh();
		}
	}

	BuildGridColPosCache();
}

void TimelinePanel::OnResize(wxSizeEvent& event)
{
	event.Skip();
	BuildGridColPosCache();
}

void TimelinePanel::OnTimelineKeyframeLeftClick(wxGridEvent& event)
{
	if(m_animation && m_actor)
	{
		int keyframeIdx = event.GetCol();

		if(keyframeIdx < m_actor->m_trackSpriteAnim.GetNumKeyframes())
		{
			float frame = m_actor->m_trackSpriteAnim.GetKeyframe(keyframeIdx).GetTime();
			m_animation->SetFrame(frame);
			SetSliderFrame(frame);
			SyncAllActors();
		}
	}
}

void TimelinePanel::OnTimelineKeyframeRightClick(wxGridEvent& event)
{
	if(m_animation && m_actor)
	{
		//Right-click menu
		wxMenu contextMenu;

		contextMenu.Append(eMenuInsertKeyframeLeft, wxString("Copy keyframe (to left)"));
		contextMenu.Append(eMenuInsertKeyframeRight, wxString("Copy keyframe (to right)"));
		contextMenu.Append(eMenuDeleteKeyframe, wxString("Delete keyframe"));
		contextMenu.Append(eMenuSetSpriteAnimLength, wxString("Set to sprite anim length"));
		contextMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&TimelinePanel::OnContextMenuClick, NULL, this);
		m_contextMenuColIdx = event.GetCol();

		PopupMenu(&contextMenu);
	}
}

void TimelinePanel::OnContextMenuClick(wxCommandEvent& event)
{
	if(m_animation && m_actor)
	{
		switch(event.GetId())
		{
			case eMenuInsertKeyframeLeft:
				break;
			case eMenuInsertKeyframeRight:
				break;
			case eMenuDeleteKeyframe:
				break;
			case eMenuSetSpriteAnimLength:
			{
				int keyframeIdx = m_contextMenuColIdx;

				if(m_actor->m_trackSpriteAnim.GetNumKeyframes() > keyframeIdx + 1)
				{
					AnimKeyframeSpriteAnim& keyframe = m_actor->m_trackSpriteAnim.GetKeyframe(keyframeIdx);
					SpriteSheetId spriteSheetId = keyframe.GetValue().first;
					SpriteAnimId spriteAnimId = keyframe.GetValue().second;

					if(GameObject* gameObject = m_project.GetEditingMap().GetGameObject(m_actor->GetGameObjectId()))
					{
						if(const GameObjectType* gameObjectType = m_project.GetGameObjectType(gameObject->GetTypeId()))
						{
							if(Actor* spriteActor = m_project.GetActor(gameObjectType->GetSpriteActorId()))
							{
								if(SpriteSheet* spriteSheet = spriteActor->GetSpriteSheet(spriteSheetId))
								{
									if(SpriteAnimation* spriteAnim = spriteSheet->GetAnimation(spriteAnimId))
									{
										float spriteAnimLength = spriteAnim->GetLength() / spriteAnim->GetPlaybackSpeed();

										float prevTimeA = keyframe.GetTime();
										float prevTimeB = m_actor->m_trackSpriteAnim.GetKeyframe(keyframeIdx + 1).GetTime();
										float prevLength = prevTimeB - prevTimeA;
										float delta = spriteAnimLength - prevLength;

										const float minTime = 0.01f;

										if(spriteAnimLength < minTime)
										{
											delta = spriteAnimLength = minTime;
										}

										//Shift all keyframes beyond current
										for(int i = keyframeIdx + 1; i < m_actor->m_trackPosition.GetNumKeyframes(); i++)
										{
											m_actor->m_trackPosition.GetKeyframe(i).SetTime(m_actor->m_trackPosition.GetKeyframe(i).GetTime() + delta);
											m_actor->m_trackSpriteAnim.GetKeyframe(i).SetTime(m_actor->m_trackSpriteAnim.GetKeyframe(i).GetTime() + delta);
										}

										//Adjust anim length
										SetAnimLength(*m_animation, *m_actor);

										//Redraw
										PopulateTimeline(*m_animation, m_actor);
									}
								}
							}
						}
					}
				}

				break;
			}
		}
	}
}