struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

float4 main(PixelInput input) : SV_TARGET
{
    //return float4(1.0f, 1.0f, 1.0f, 1.0f);
    //return float4(input.color, 1.0f);

    // Light Dir.
    float3 lightDir = -float3(500.0f, 500.0f, -500.0f);
    lightDir = normalize(lightDir);
    
    // World Normal.
    float3 worldNormal = normalize(input.normal);

    // Dot.
    float lightIntensity = saturate(dot(worldNormal, -lightDir));
    
    return lightIntensity;
}