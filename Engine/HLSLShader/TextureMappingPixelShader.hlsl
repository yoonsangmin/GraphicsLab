struct PixelInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 textColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    //return float4(1.0f, 1.0f, 1.0f, 1.0f);
    //return float4(input.color, 1.0f);
    //return float4(input.texCoord.r, 1.0f - input.texCoord.r, input.texCoord.g, 1.0f);
    return textColor;
}