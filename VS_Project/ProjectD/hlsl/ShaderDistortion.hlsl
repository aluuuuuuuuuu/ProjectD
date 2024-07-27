// 頂点シェーダー
struct VS_INPUT
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    float4 worldPosition = mul(float4(input.Pos, 1.0f), World);
    float4 viewPosition = mul(worldPosition, View);
    output.Pos = mul(viewPosition, Projection);
    output.UV = input.UV;
    return output;
}

// ピクセルシェーダー
SamplerState samp : register(s0);
Texture2D texture0 : register(t0);

float4 PS(PS_INPUT input) : SV_TARGET
{
    // 画面中央を(0.5, 0.5)とする
    float2 center = float2(0.5, 0.5);
    float2 uv = input.UV;

    // 中心からの距離を計算
    float2 offset = uv - center;
    float distance = length(offset);

    // 距離に応じて歪みを適用
    if (distance > 0.3) // 0.3は歪みを開始する距離
    {
        // 歪み係数を計算
        float distortionAmount = (distance - 0.3) * 2.0; // 2.0は歪みの強さ
        uv = center + offset * (1.0 + distortionAmount);
    }

    // テクスチャから色をサンプリング
    float4 color = texture0.Sample(samp, uv);
    return color;
}