
// Lambert cosine law.
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
	return saturate(dot(worldNormal, -lightDirection));
}

// Half Lambert.
float CalcHalfLambert(float3 worldNormal, float3 lightDirection, float param = 2)
{
	float NoL = CalcLambert(worldNormal, lightDirection);
	return pow(NoL * 0.5f + 0.5f, param);
}

// Phong.
float CalcPhong(
	float3 worldNormal,
	float3 lightDirection,
	float3 cameraDirection,
	float shininess = 16.0f)
{
	float NoL = CalcLambert(worldNormal, lightDirection);

	float specular = 0;
	if (NoL > 0)
	{
		float3 reflection = reflect(lightDirection, worldNormal);
		float3 viewDirection = normalize(cameraDirection);
		float RoV = saturate(dot(reflection, -viewDirection));
		specular = pow(RoV, shininess);
	}

	return specular;
}

// Blinn-Phong.
float CalcBlinnPhong(
	float3 worldNormal,
	float3 lightDirection,
	float3 cameraDirection,
	float shininess = 32.0f)
{
	float NoL = CalcLambert(worldNormal, lightDirection);

	float specular = 0;
	if (NoL > 0)
	{
		// Half Vector.
		float3 viewDirection = normalize(cameraDirection);
		float3 halfVector = normalize((-lightDirection) + (-viewDirection));

		// NoH.
		float NoH = saturate(dot(worldNormal, halfVector));
		specular = pow(NoH, shininess);
	}

	return specular;
}