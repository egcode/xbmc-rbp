#ifndef WINDOW_SYSTEM_DFB_H
#define WINDOW_SYSTEM_DFB_H

#pragma once

/*
 *      Copyright (C) 2011 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "rendering/gles/RenderSystemGLES.h"
#include "utils/GlobalsHandling.h"
#include "windowing/WinSystem.h"

typedef struct _IDirectFB IDirectFB;
typedef struct _IDirectFBScreen IDirectFBScreen;
typedef struct _IDirectFBSurface IDirectFBSurface;
typedef struct _IDirectFBDisplayLayer IDirectFBDisplayLayer;
typedef struct _IDirectFBDataBuffer IDirectFBDataBuffer;
typedef struct _IDirectFBImageProvider IDirectFBImageProvider;

class CWinBindingEGL;

class CWinSystemDFB : public CWinSystemBase, public CRenderSystemGLES
{
public:
  CWinSystemDFB();
  virtual ~CWinSystemDFB();

  virtual bool  InitWindowSystem();
  virtual bool  DestroyWindowSystem();
  virtual bool  CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool  DestroyWindow();
  virtual bool  ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool  SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void  UpdateResolutions();
  virtual bool  IsExtSupported(const char* extension);

  virtual void  ShowOSMouse(bool show);

  virtual void  NotifyAppActiveChange(bool bActivated);

  virtual bool  Minimize();
  virtual bool  Restore() ;
  virtual bool  Hide();
  virtual bool  Show(bool raise = true);

  IDirectFB*    GetIDirectFB() const;
  bool          CreateImageProvider(IDirectFBDataBuffer *buffer, IDirectFBImageProvider **provider, bool retain1st);
  bool          ReleaseImageProvider(IDirectFBImageProvider *provider);

protected:
  virtual bool  PresentRenderImpl();
  virtual void  SetVSyncImpl(bool enable);
  
  CWinBindingEGL        *m_eglBinding;
  IDirectFB             *m_dfb;
  IDirectFBScreen       *m_dfb_screen;
  IDirectFBDisplayLayer *m_dfb_layer;
  IDirectFBSurface      *m_dfb_surface;
  int                    m_buffermode;
  IDirectFBImageProvider *m_dfb_image_provider;
};

XBMC_GLOBAL_REF(CWinSystemDFB,g_Windowing);
#define g_Windowing XBMC_GLOBAL_USE(CWinSystemDFB)

#endif // WINDOW_SYSTEM_DFB_H