#pragma once

#include <SFML/Graphics.hpp>

#include "../../misc/matrix/Matrix3X1.h"
#include "../../misc/matrix/Matrix3X3.h"

#include "../AbstractObject.h"

#include "../../misc/config.hpp"

namespace projection {
	class Renderable : public AbstractObject
	{
	protected:
		Renderable();

		sf::RenderTarget* m_Target;

		std::vector<sf::VertexArray> m_Vertices;
		sf::Color m_Color;

		sf::Vector3f* m_GlobalOffset;

	public:
		bool m_IsTextured;

		virtual void render(sf::RenderTarget* target, sf::Uint8* buffer = nullptr) = 0;
		virtual void applyPerspective() = 0;

		virtual void rotateX(float angle) = 0;
		virtual void rotateY(float angle) = 0;
		virtual void rotateZ(float angle) = 0;

		virtual void rotateX(float angle, sf::Vector3f refPosition) = 0;
		virtual void rotateY(float angle, sf::Vector3f refPosition) = 0;
		virtual void rotateZ(float angle, sf::Vector3f refPosition) = 0;

		virtual void rotateByCamera(float angle, sf::Vector3f refPosition) = 0;

		virtual std::vector<AbstractObject*> getChildren() override;

		std::vector<sf::VertexArray>* getVertices();
		virtual void setGlobalOffset(sf::Vector3f* vec);

		template
			<typename T> void clamp(T min, T* value, T max);

		sf::Vector2f translateToRel(sf::Vector2f pos, sf::Vector2u windowSize);
	};

	template<typename T>
	inline void Renderable::clamp(T min, T* value, T max)
	{
		if (*value > max) *value = max;
		else if (*value < min) *value = min;
	}
}

