//------------------------------------------------------------------------------
//  testviewerapplication.cc
//  (C) 2006 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "tools/testviewer/testviewerapplication.h"
#include "debugrender/debugrender.h"

namespace Tools
{
using namespace CoreGraphics;
using namespace Graphics;
using namespace Math;
using namespace Util;
using namespace Resources;
using namespace Timing;

//------------------------------------------------------------------------------
/**
*/
TestViewerApplication::TestViewerApplication()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
TestViewerApplication::~TestViewerApplication()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
TestViewerApplication::Open()
{
    n_assert(!this->IsOpen());
    if (ViewerApplication::Open())
    {
        // setup lights
        matrix44 lightTransform = matrix44::rotationx(n_deg2rad(-70.0f));
        this->globalLight = GlobalLightEntity::Create();
        this->globalLight->SetTransform(lightTransform);
        this->globalLight->SetColor(float4(0.0f, 0.0f, 0.5f, 0.0f));
        this->globalLight->SetBackLightColor(float4(0.0f, 0.0f, 0.0f, 0.0f));
        this->globalLight->SetCastShadows(false);
        this->stage->AttachEntity(this->globalLight.cast<GraphicsEntity>());

        lightTransform = matrix44::multiply(matrix44::scaling(75.0f, 75.0f, 100.0f), matrix44::lookatrh(point(20.0f, 20.0f, 20.0f), point::origin(), vector::upvec()));
        this->localLight0 = SpotLightEntity::Create();
        this->localLight0->SetTransform(lightTransform);
        this->localLight0->SetColor(float4(1.0f, 1.0f, 1.0f, 0.0f));        
        this->localLight0->SetCastShadows(true);
        this->stage->AttachEntity(this->localLight0.cast<GraphicsEntity>());

        // setup models
        this->ground = ModelEntity::Create();
        this->ground->SetResourceId(ResourceId("mdl:examples/shadowtest.n2"));
        this->stage->AttachEntity(ground.cast<GraphicsEntity>());

        this->model = ModelEntity::Create();
        this->model->SetTransform(matrix44::translation(0.0f, 3.0f, 0.0f));
        this->model->SetResourceId(ResourceId("mdl:examples/box.n2"));        
        this->stage->AttachEntity(this->model.cast<GraphicsEntity>());

        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
TestViewerApplication::Close()
{
    this->stage->RemoveEntity(this->globalLight.cast<GraphicsEntity>());
    this->stage->RemoveEntity(this->localLight0.cast<GraphicsEntity>());
    this->stage->RemoveEntity(this->ground.cast<GraphicsEntity>());
    this->stage->RemoveEntity(this->model.cast<GraphicsEntity>());
    this->globalLight = 0;
    this->localLight0 = 0;
    this->ground = 0;
    this->model = 0;

    ViewerApplication::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
TestViewerApplication::OnUpdateFrame()
{
    point lookatPos = this->model->GetTransform().getrow3();

    // animate lights
    float curTime = (float) this->GetTime();
    point pos(20.0f * n_sin(curTime), 
              20.0f + 15.0f * n_sin(curTime * 0.5f), 
              20.0f + 7.5f * n_sin(curTime * 0.33f));
    matrix44 lightTransform = matrix44::multiply(matrix44::scaling(75.0f, 75.0f, 100.0f), matrix44::lookatrh(pos, lookatPos, vector::upvec()));
    this->localLight0->SetTransform(lightTransform);

    float frameTime = (float)this->GetFrameTime();
    Util::String fpsTxt;
    fpsTxt.Format("FPS: %.2f", 1/frameTime);
    _debug_text(fpsTxt, Math::float2(0.0,0.0), Math::float4(1,1,1,1))

    ViewerApplication::OnUpdateFrame();
}

} // namespace Tools