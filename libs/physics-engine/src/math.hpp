#pragma once

namespace pmframework
{
    const float SCALAR_TOLERANCE = 0.000001f;
    const float PI = 3.14159265358979f;
    typedef float scalar;

    class Vector3d
    {
    private:
        scalar x, y, z;

    public:
        PHYSICSENGINE_API Vector3d(void);
        PHYSICSENGINE_API Vector3d(scalar xComponent, scalar yComponent, scalar zComponent);
        PHYSICSENGINE_API Vector3d(const Vector3d &rightOperand);

        PHYSICSENGINE_API void X(scalar xComponent);
        PHYSICSENGINE_API scalar X(void);

        PHYSICSENGINE_API void Y(scalar yComponent);
        PHYSICSENGINE_API scalar Y(void);

        PHYSICSENGINE_API void Z(scalar zComponent);
        PHYSICSENGINE_API scalar Z(void);

        PHYSICSENGINE_API void SetXYZ(scalar xComponent, scalar yComponent, scalar zComponent);
        PHYSICSENGINE_API void GetXYZ(scalar &xCompoenet, scalar &yComponent, scalar &zComponent);

        PHYSICSENGINE_API Vector3d &operator = (const Vector3d &rightOperand);

        PHYSICSENGINE_API Vector3d operator +(const Vector3d &rightOperand);
        PHYSICSENGINE_API Vector3d operator +=(const Vector3d &rightOperand);
        PHYSICSENGINE_API Vector3d operator -(const Vector3d &rightOperand);
        PHYSICSENGINE_API Vector3d operator -=(const Vector3d &rightOperand);
        PHYSICSENGINE_API Vector3d operator *(scalar rightOperand);
        friend Vector3d operator *(scalar leftOperand, const Vector3d &rightOperand);

        PHYSICSENGINE_API Vector3d operator *=(scalar rightOperand);
        PHYSICSENGINE_API Vector3d operator /(scalar rightOperand);
        PHYSICSENGINE_API void operator /=(scalar rightOperand);

        PHYSICSENGINE_API scalar dotProduct(const Vector3d &v1);
        PHYSICSENGINE_API scalar norm(void);
        PHYSICSENGINE_API scalar normSquared(void);

        PHYSICSENGINE_API Vector3d crossProduct(const Vector3d &rightOperand);
        PHYSICSENGINE_API Vector3d normalize(scalar tolerance);

    };

    inline Vector3d::Vector3d(void)
    {
        x = y = z = 0;
    }

    inline Vector3d::Vector3d(scalar xComponent, scalar yComponent, scalar zComponent)
    {
        x = xComponent;
        y = yComponent;
        z = zComponent;
    }

    inline Vector3d::Vector3d(const Vector3d &sourceVector)
    {
        x = sourceVector.x;
        y = sourceVector.y;
        z = sourceVector.z;
    }

    inline void Vector3d::X(scalar xComponent)
    {
        x = xComponent;
    }

    inline scalar Vector3d::X(void)
    {
        return x;
    }

    inline void Vector3d::Y(scalar yComponent)
    {
        y = yComponent;
    }

    inline scalar Vector3d::Y(void)
    {
        return y;
    }

    inline void Vector3d::Z(scalar zComponent)
    {
        z = zComponent;
    }

    inline scalar Vector3d::Z(void)
    {
        return z;
    }

    inline void Vector3d::SetXYZ(scalar xComponent, scalar yComponent, scalar zComponent)
    {
        x = xComponent;
        y = yComponent;
        z = zComponent;
    }

    inline void Vector3d::GetXYZ(scalar &xComponent, scalar &yComponent, scalar &zComponent)
    {
        xComponent = x;
        yComponent = y;
        zComponent = z;
    }

    inline Vector3d &Vector3d::operator =(const Vector3d &rightOperand)
    {
        x = rightOperand.x;
        y = rightOperand.y;
        z = rightOperand.z;

        return (*this);
    }

    inline Vector3d Vector3d::operator +(const Vector3d &rightOperand)
    {
        return(Vector3d(x + rightOperand.x, y + rightOperand.y, z + rightOperand.z));
    }
    inline Vector3d Vector3d::operator -(const Vector3d &rightOperand)
    {
        return(Vector3d(x - rightOperand.x, y - rightOperand.y, z - rightOperand.z));
    }
    inline Vector3d Vector3d::operator +=(const Vector3d &rightOperand)
    {
        x += rightOperand.x;
        y += rightOperand.y;
        z += rightOperand.z;
        return (*this);
    }
    inline Vector3d Vector3d::operator -=(const Vector3d &rightOperand)
    {
        x -= rightOperand.x;
        y -= rightOperand.y;
        z -= rightOperand.z;
        return (*this);
    }
    inline Vector3d Vector3d::operator *(scalar rightOperand)
    {
        return(Vector3d(x * rightOperand, y * rightOperand, z * rightOperand));
    }

    inline Vector3d operator *(scalar leftOperand, const Vector3d &rightOperand)
    {
        return (Vector3d(leftOperand*rightOperand.x,
            leftOperand*rightOperand.y,
            leftOperand*rightOperand.z));
    }
    inline Vector3d Vector3d::operator *=(scalar rightOperand)
    {
        x *= rightOperand;
        y *= rightOperand;
        z *= rightOperand;
        return (*this);
    }
    inline Vector3d Vector3d::operator /(scalar rightOperand)
    {
        return (Vector3d(x / rightOperand, y / rightOperand, z / rightOperand));
    }

    inline void Vector3d::operator /=(scalar rightOperand)
    {
        x /= rightOperand;
        y /= rightOperand;
        z /= rightOperand;
    }

    inline scalar Vector3d::dotProduct(const Vector3d &v1)
    {
        return (x*v1.x + y*v1.y + z*v1.z);
    }
    inline scalar Vector3d::norm(void)
    {
        return (sqrt(x*x + y*y + z*z));
    }

    inline scalar Vector3d::normSquared(void)
    {
        return (x*x + y*y + z*z);
    }

    inline Vector3d Vector3d::crossProduct(const Vector3d &rightOperand)
    {
        return(Vector3d(y*rightOperand.z - z*rightOperand.y,
            z*rightOperand.x - x*rightOperand.z,
            x*rightOperand.y - y*rightOperand.x));
    }

    inline Vector3d Vector3d::normalize(scalar tolerance)
    {
        Vector3d result;

        scalar length = norm();
        if (length >= tolerance) {
            result.x = x / length;
            result.y = y / length;
            result.z = z / length;
        }
        return result;
    }


    // matrix3x3 class의 함수들은 chris hacker를 참조하였습니다.

    class Matrix3x3
    {
    public:

        PHYSICSENGINE_API Matrix3x3(void);
        PHYSICSENGINE_API Matrix3x3(scalar(*pElements)[3]);

        enum mode { SkewSymmetric, Zero };
        PHYSICSENGINE_API inline Matrix3x3(mode MustBeZero);
        PHYSICSENGINE_API inline Matrix3x3(Vector3d CrossVector, mode MustBeSkewSymmetric);

        PHYSICSENGINE_API inline Matrix3x3 &operator+=(Matrix3x3 const &A);

        PHYSICSENGINE_API inline scalar &operator()(int unsigned Row, int unsigned Column);
        PHYSICSENGINE_API inline scalar const &operator()(int unsigned Row, int unsigned Column) const;

        PHYSICSENGINE_API inline scalar GetElement(int Row, int Column) const;
        PHYSICSENGINE_API inline Matrix3x3 &SetElement(int Row, int Column, scalar Value);

    protected:
        scalar aElements[3][3];
    };

    inline scalar &Matrix3x3::operator()(int unsigned Row, int unsigned Column)
    {
        assert((Row < 3) && (Column < 3));
        return aElements[Row][Column];
    }

    inline scalar const &Matrix3x3::operator()(int unsigned Row,
        int unsigned Column) const
    {
        assert((Row < 3) && (Column < 3));
        return aElements[Row][Column];
    }

    PHYSICSENGINE_API void OrthonormalizeOrientation(Matrix3x3 &Orientation);

    inline scalar Matrix3x3::GetElement(int Row, int Column) const
    {
        return aElements[Row][Column];
    }

    inline Matrix3x3 &Matrix3x3::SetElement(int Row, int Column, scalar Value)
    {
        aElements[Row][Column] = Value;

        return *this;
    }

    inline Matrix3x3::Matrix3x3(scalar(*pElements)[3])
    {
        assert(pElements);

        Matrix3x3 &M = *this;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                M(i, j) = pElements[i][j];
            }
        }
    }

    inline Matrix3x3::Matrix3x3(Vector3d Vector, mode Mode)
    {
        assert(Mode == SkewSymmetric);

        Matrix3x3 &M = *this;

        M(0, 0) = 0;           M(0, 1) = -Vector.Z(); M(0, 2) = Vector.Y();
        M(1, 0) = Vector.Z();  M(1, 1) = 0;           M(1, 2) = -Vector.X();
        M(2, 0) = -Vector.Y(); M(2, 1) = Vector.X();  M(2, 2) = 0;
    }

    inline Matrix3x3::Matrix3x3(mode Mode)
    {
        assert(Mode == Zero);

        for (int Counter = 0; Counter < 3; Counter++)
        {
            aElements[Counter][0] = 0;
            aElements[Counter][1] = 0;
            aElements[Counter][2] = 0;
        }
    }

    inline Matrix3x3 Transpose(Matrix3x3 const &Matrix)
    {
        Matrix3x3 Return;

        for (int Counter = 0; Counter < 3; Counter++)
        {
            Return(0, Counter) = Matrix(Counter, 0);
            Return(1, Counter) = Matrix(Counter, 1);
            Return(2, Counter) = Matrix(Counter, 2);
        }

        return Return;
    }

    PHYSICSENGINE_API Matrix3x3 operator*(Matrix3x3 const &Multiplicand, Matrix3x3 const &Multiplier);

    PHYSICSENGINE_API Vector3d operator*(Matrix3x3 const &Multiplicand, Vector3d Multiplier);

    inline Matrix3x3 operator+(Matrix3x3 const &Operand1, Matrix3x3 const &Operand2)
    {
        Matrix3x3 Return;

        for (int Counter = 0; Counter < 3; Counter++)
        {
            Return(0, Counter) = Operand1(0, Counter) + Operand2(0, Counter);
            Return(1, Counter) = Operand1(1, Counter) + Operand2(1, Counter);
            Return(2, Counter) = Operand1(2, Counter) + Operand2(2, Counter);
        }

        return Return;
    }

    inline Matrix3x3 operator-(Matrix3x3 const &Operand1, Matrix3x3 const &Operand2)
    {
        Matrix3x3 Return;

        for (int Counter = 0; Counter < 3; Counter++)
        {
            Return(0, Counter) = Operand1(0, Counter) - Operand2(0, Counter);
            Return(1, Counter) = Operand1(1, Counter) - Operand2(1, Counter);
            Return(2, Counter) = Operand1(2, Counter) - Operand2(2, Counter);
        }

        return Return;
    }

    inline Matrix3x3 operator*(scalar const Value, Matrix3x3 const &Matrix)
    {
        Matrix3x3 Return;

        for (int Counter = 0; Counter < 3; Counter++)
        {
            Return(0, Counter) = Value * Matrix(0, Counter);
            Return(1, Counter) = Value * Matrix(1, Counter);
            Return(2, Counter) = Value * Matrix(2, Counter);
        }

        return Return;
    }

    inline Matrix3x3 &Matrix3x3::operator+=(Matrix3x3 const &Operand1)
    {
        for (int Counter = 0; Counter < 3; Counter++)
        {
            aElements[0][Counter] += Operand1(0, Counter);
            aElements[1][Counter] += Operand1(1, Counter);
            aElements[2][Counter] += Operand1(2, Counter);
        }

        return *this;
    }

    inline Matrix3x3 operator*(Matrix3x3 const &Matrix, scalar const Value)
    {
        return Value * Matrix;
    }

    inline Matrix3x3 operator-(Matrix3x3 const &Matrix)
    {
        Matrix3x3 Return;

        for (int Counter = 0; Counter < 3; Counter++)
        {
            Return(0, Counter) = -Matrix(0, Counter);
            Return(1, Counter) = -Matrix(1, Counter);
            Return(2, Counter) = -Matrix(2, Counter);
        }

        return Return;
    }
}