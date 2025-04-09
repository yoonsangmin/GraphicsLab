struct PixelInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	// Sampling.
	float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

	// Light Dir.
	float3 lightDir = -float3(500.0f, 500.0f, -500.0f);
	lightDir = normalize(lightDir);

	// World Normal.
	float3 worldNormal = normalize(input.normal);

	// Dot.
	// float lightIntensity = max(0.0f, dot(worldNormal, lightDir));
	float lightIntensity = saturate(dot(worldNormal, -lightDir));
	//float lightIntensity1 = dot(worldNormal, -lightDir);

	float4 finalColor = texColor * lightIntensity;
	
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(input.color, 1.0f);
	//return float4(input.texCoord.r, 1.0f - input.texCoord.r, input.texCoord.g, 1.0f);
	//return float4(finalColor,lightIntensity, lightIntensity, 1);
	return finalColor;
}
