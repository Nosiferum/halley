/*****************************************************************\
           __
          / /
		 / /                     __  __
		/ /______    _______    / / / / ________   __       __
	   / ______  \  /_____  \  / / / / / _____  | / /      / /
	  / /      | / _______| / / / / / / /____/ / / /      / /
	 / /      / / / _____  / / / / / / _______/ / /      / /
	/ /      / / / /____/ / / / / / / |______  / |______/ /
   /_/      /_/ |________/ / / / /  \_______/  \_______  /
                          /_/ /_/                     / /
			                                         / /
		       High Level Game Framework            /_/

  ---------------------------------------------------------------

  Copyright (c) 2007-2011 - Rodrigo Braz Monteiro.
  This file is subject to the terms of halley_license.txt.

\*****************************************************************/

#pragma once

#include <array>
#include "angle.h"
#include "vector2.h"

namespace Halley {
	class Matrix4f {
	public:
		Matrix4f();
		Matrix4f(const Matrix4f& m);
		Matrix4f(Matrix4f&& m) noexcept;
		Matrix4f(const float elements[]);

		Matrix4f& operator=(const Matrix4f& param);
		Matrix4f& operator*=(const Matrix4f& param);
		Matrix4f operator*(const Matrix4f& param) const;
		Vector2f operator*(const Vector2f& param) const;

		static Matrix4f makeIdentity();
		static Matrix4f makeRotationX(Angle1f angle);
		static Matrix4f makeRotationY(Angle1f angle);
		static Matrix4f makeRotationZ(Angle1f angle);
		static Matrix4f makeScaling(Vector2f scale);
		static Matrix4f makeTranslation(Vector2f translation);
		static Matrix4f makeOrtho2D(float left, float right, float bottom, float top, float near, float far);

		void loadIdentity();
		void rotateZ(Angle1f angle);
		void scale(Vector2f scale);
		void translate(Vector2f translation);
		void transpose();

		float* getElements();
		const float* getElements() const;

		constexpr static size_t getIndex(size_t column, size_t row)
		{
			return 4 * column + row;
		}

		float getElement(size_t column, size_t row) const
		{
			return elements[getIndex(column, row)];
		}

		inline float& getElement(size_t column, size_t row)
		{
			return elements[getIndex(column, row)];
		}

	private:
		std::array<float, 16> elements;
	};
}