#pragma once
#include <glm/glm.hpp>
#include <cstdint>
#include "pipeline_layout.hpp"
#include "pipeline.hpp"

enum class krxPrimitiveType
{
	POINTS,
	LINES,
	TRIANGLES
};

enum class krxRasterizerFacing
{
	CW,
	CCW
};

enum class krxRasterizerFeature : uint8_t
{
	DEPTH_TESTING = 1ul << 0,
	ONLY_DEPTH = 1ul << 1
};

class krxContext
{
private:
	void draw_triangle(const uint32_t VertexStart, const uint32_t VertexCount);
private:
	krxPipelineLayout* PipelineLayout = nullptr;
	krxShaderPipeline* ShaderPipeline = nullptr;
public:
	struct krxRast
	{
	private:
		friend class krxContext;
		krxPrimitiveType PrimitiveType = krxPrimitiveType::TRIANGLES;
		krxRasterizerFacing Facing = krxRasterizerFacing::CCW;
		uint8_t Features = 0;

		struct
		{
			glm::uvec2 Position;
			glm::uvec2 Size;
		} Viewport;
	public:
		void set_primitive_type(const krxPrimitiveType PrimitiveType);
		void set_facing(const krxRasterizerFacing Facing);
		void set_viewport(const glm::uvec2& Position, const glm::uvec2& Size);
		void enable_feature(const krxRasterizerFeature Feature);
		void disable_feature(const krxRasterizerFeature Feature);
	} Rasterizer;

	void bind_shader_pipeline(krxShaderPipeline* Pipeline);
	void bind_pipeline_layout(krxPipelineLayout* Layout);
	void clear_color_targets(const glm::vec4 RGBA);
	void fast_clear_color_targets();
	void clear_depth_target();
	void draw(const uint32_t VertexStart, const uint32_t VertexCount);
};