// ���_�V�F�[�_�[
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

// �s�N�Z���V�F�[�_�[
SamplerState samp : register(s0);
Texture2D texture0 : register(t0);

float4 PS(PS_INPUT input) : SV_TARGET
{
    // ��ʒ�����(0.5, 0.5)�Ƃ���
    float2 center = float2(0.5, 0.5);
    float2 uv = input.UV;

    // ���S����̋������v�Z
    float2 offset = uv - center;
    float distance = length(offset);

    // �����ɉ����Ęc�݂�K�p
    if (distance > 0.3) // 0.3�͘c�݂��J�n���鋗��
    {
        // �c�݌W�����v�Z
        float distortionAmount = (distance - 0.3) * 2.0; // 2.0�͘c�݂̋���
        uv = center + offset * (1.0 + distortionAmount);
    }

    // �e�N�X�`������F���T���v�����O
    float4 color = texture0.Sample(samp, uv);
    return color;
}