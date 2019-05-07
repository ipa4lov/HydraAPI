float4 main(const SurfaceInfo* sHit, float4 a, float4 b)
{
  const float4 res = a * b;
  //return make_float4(1, 1, 1, 1);
  return make_float4(res.x, res.y, res.z, 1);
}
