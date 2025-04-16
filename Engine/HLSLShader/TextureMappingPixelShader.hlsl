#include "Common.hlsli"

struct PixelInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
	float3 cameraDirection : TEXTCOORD1;
	float3 tangent : TANGENT;
	float3 bitangent : BITANGENT;
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

	// Dot (Lambert cosine law).
	//float nDotL = saturate(dot(worldNormal, -lightDir));
	float nDotL = CalcHalfLambert(worldNormal, lightDir);
	// float nDotL = max(0.0f, dot(worldNormal, lightDir));

	// Half Lambert.
	// nDotL = pow((nDotL * 0.7f) + (1.0f - 0.7f), 1.0f);

	float4 ambient = texColor * float4(0.2f, 0.2f, 0.2f, 1);
	float4 diffuse = texColor * nDotL;
	float4 finalColor = ambient + diffuse;
	
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(input.color, 1.0f);
	//return float4(input.texCoord.r, 1.0f - input.texCoord.r, input.texCoord.g, 1.0f);
	//return float4(finalColor,lightIntensity, lightIntensity, 1);

	// Phong (specular).
	//float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);
	// if (nDotL)
	// {
	// 	float3 reflection = reflect(lightDir, worldNormal);
	// 	float3 viewDirection = normalize(input.cameraDirection);
	// 	float rDotV = saturate(dot(reflection, -viewDirection));
	// 	float shininess = 16.0f;
	// 	specular = pow(rDotV, shininess);
	// }

	// Blinn-Phong (specular).
	float specular = CalcBlinnPhong(worldNormal, lightDir, input.cameraDirection);
	// if (nDotL)
	// {
	// 	// Half Vector.
	// 	float3 viewDirection = normalize(input.cameraDirection);
	// 	float3 halfVector = normalize((-lightDir) + (-viewDirection));
	//
	// 	// nDotH.
	// 	float nDotH = saturate(dot(worldNormal, halfVector));
	// 	float shininess = 32.0f;
	// 	specular = pow(nDotH, shininess);
	// }

	finalColor += float4(0.4f, 0.6f, 0.8f, 1) * specular;
	//finalColor += texColor * specular;
	//return float4(specular, specular, specular, 1);
	return finalColor;
}
