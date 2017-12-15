#pragma once

namespace Persimmon
{
enum RenderFlag
{
    DrawParentBackground = 0x1,		/* if it's a transparent widget, render background. */
    DrawChildren = 0x2,			  	/* draw children widgets. */
    DrawComposed = 0x4,	          	/* do composed render */
    DrawNormal = (0x1 | 0x2 | 0x4), /* normally drawing */
};
};

