/*
FileCopyEx - Extended File Copy plugin for Far 2 file manager

Copyright (C) 2004 - 2010
Idea & core: Max Antipin
Coding: Serge Cheperis aka craZZy
Bugfixes: slst, CDK, Ivanych, Alter, Axxie and Nsky
Special thanks to Vitaliy Tsubin
Far 2 (32 & 64 bit) full unicode version by djdron

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Framework/StdHdr.h"
#include "taskbarIcon.h"
#include "Common.h"
#include "guid.hpp"

TaskBarIcon::TaskBarIcon() : last_state(S_NO_PROGRESS)
{
}

TaskBarIcon::~TaskBarIcon()
{
  if (last_state != S_NO_PROGRESS)
    SetState(S_NO_PROGRESS);
}
void TaskBarIcon::SetState(State state, float param)
{
  switch (state)
  {
    case S_PROGRESS:
      if (param > 1.0f)
      {
        param = 1.0f;
      }
      if (param < 0.0f)
      {
        param = 0.0f;
      }
      ProgressValue pv;
      pv.Completed = (int64_t)(param * 100.0f);
      pv.Total = 100;
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSSTATE, TBPS_NORMAL, nullptr);
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSVALUE, 0, &pv);
      break;

    case S_NO_PROGRESS:
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSSTATE, TBPS_NOPROGRESS, nullptr);
      break;
    case S_WORKING:
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSSTATE, TBPS_INDETERMINATE, nullptr);
      break;
    case S_ERROR:
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSSTATE, TBPS_ERROR, nullptr);
      break;
    case S_PAUSED:
      Info.AdvControl(&MainGuid, ACTL_SETPROGRESSSTATE, TBPS_PAUSED, nullptr);
      break;
  }
  last_state = state;
}
