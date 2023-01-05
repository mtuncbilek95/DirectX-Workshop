struct vOut
{
	float3 color : Color;
	float4 pos : SV_Position;
};

cbuffer CBuffer
{
	column_major matrix transform;
}

vOut main( float3 pos : Position, float3 color : Color )
{
	vOut vso;
	vso.pos = mul(float4(pos,1.0f),transform);
	vso.color = color;
	return vso;
}