#pragma once

// FOV - not used yet
#define c_FOV 80.f

// Distance from Camera to projection plane
#define c_viewPortDistance (-1 / tan((c_FOV / 2.0) * 3.14159265 / 180.0))

// Rendering options
#define c_z_clipping 0.8f

// Window options
#define c_winWidth 2140
#define c_winHeight 1200
#define c_framerate 60

// Widgets
#define c_Padding 10.f
#define c_PaddingTop 30.f

#define c_objectBrowserHeight 500.f
#define c_objectBrowserWidth 300.f

#define c_objectAttrHeight 1160.f
#define c_objectAttrWidth 420.f

#define c_diagnosticsHeight 70.f
#define c_diagnosticsWidth 300.f

// PI
#define c_PI 3.14159265f
