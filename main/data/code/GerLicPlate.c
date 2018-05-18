// procedure texture test

float4 userProc(const SurfaceInfo* sHit, sampler2D tex1, __global sampler2D tex2[8], float2 texOffset, float4 inColor)
{
  
  const float2 texCoord = readAttr(sHit,"TexCoord0");
  
  float4 texColorBase = texture2D(tex1, texCoord + texOffset, TEX_CLAMP_U | TEX_CLAMP_V);
  
  float offsetX = 0;
  float offsetY = 0;
  float4 texColorLayout = 1.0f;
  float4 texColorFont = 1.0f;

  if(texCoord.x > 0.075f && texCoord.x < 0.17f && texCoord.y > 0.17f && texCoord.y < 0.67f) // width 0.095
  {
    offsetX = -0.075f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[5], make_float2((texCoord.x + offsetX) * 10.5263f, (texCoord.y + offsetY) * 2.0f), TEX_CLAMP_U | TEX_CLAMP_V);
    
    // texColorLayout = make_float4(1.0f, 0.5f, 0.5f, 0.0f);
  }
  else if(texCoord.x > 0.2f && texCoord.x < 0.288f && texCoord.y > 0.17f && texCoord.y < 0.81f) 
  {
    offsetX = -0.2f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[0], make_float2((texCoord.x + offsetX) * 11.36f, (texCoord.y + offsetY) * 1.5625f), TEX_CLAMP_U | TEX_CLAMP_V);

    //texColorLayout = make_float4(1.0f, 0.5f, 0.5f, 0.0f);
  }
  else if(texCoord.x > 0.302f && texCoord.x < 0.392f && texCoord.y > 0.17f && texCoord.y < 0.81f) 
  {
    offsetX = -0.302f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[1], make_float2((texCoord.x + offsetX) * 11.36f, (texCoord.y + offsetY) * 1.5625f), TEX_CLAMP_U | TEX_CLAMP_V);

    //texColorLayout = make_float4(1.0f, 0.5f, 0.5f, 0.0f);
  }
  else if(texCoord.x > 0.406f && texCoord.x < 0.496f && texCoord.y > 0.17f && texCoord.y < 0.81f) 
  {
    offsetX = -0.406f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[2], make_float2((texCoord.x + offsetX) * 11.36f, (texCoord.y + offsetY) * 1.5625f), TEX_CLAMP_U | TEX_CLAMP_V);

    //texColorLayout = make_float4(1.0f, 0.5f, 0.5f, 0.0f);
  }
  else if(texCoord.x > 0.52f && texCoord.x < 0.615f && texCoord.y > 0.17f && texCoord.y < 0.675f) 
  {
    offsetX = -0.52f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[6], make_float2((texCoord.x + offsetX) * 10.5263f, (texCoord.y + offsetY) * 2), TEX_CLAMP_U | TEX_CLAMP_V);
    
    // texColorLayout = make_float4(1.0, 0.5, 0.5, 0);
  }
  else if(texCoord.x > 0.635f && texCoord.x < 0.73f && texCoord.y > 0.17f && texCoord.y < 0.675f) 
  {
    offsetX = -0.635f;
    offsetY = -0.17f;
    texColorFont = texture2D(tex2[7], make_float2((texCoord.x + offsetX) * 10.5263f, (texCoord.y + offsetY) * 2), TEX_CLAMP_U | TEX_CLAMP_V);
    
    // texColorLayout = make_float4(1.0, 0.5, 0.5, 0);
  }
  else if(texCoord.x > 0.772f && texCoord.x < 0.844f && texCoord.y > 0.365f && texCoord.y < 0.87f) 
  {
    offsetX = -0.772f;
    offsetY = -0.365f;
    texColorFont = texture2D(tex2[3], make_float2((texCoord.x + offsetX) * 13.88f, (texCoord.y + offsetY) * 1.98f), TEX_CLAMP_U | TEX_CLAMP_V);

    //texColorLayout = make_float4(1.0, 0.5, 0.5, 0);
  }
  else if(texCoord.x > 0.855f && texCoord.x < 0.927f && texCoord.y > 0.365f && texCoord.y < 0.87f) 
  {
    offsetX = -0.855f;
    offsetY = -0.365f;
    texColorFont = texture2D(tex2[4], make_float2((texCoord.x + offsetX) * 13.88f, (texCoord.y + offsetY) * 1.98f), TEX_CLAMP_U | TEX_CLAMP_V);

    //texColorLayout = make_float4(1.0, 0.5, 0.5, 0);
  }
  

  const float4 texColorOut = texColorBase * texColorFont; // * texColorLayout;
  return texColorOut;
}