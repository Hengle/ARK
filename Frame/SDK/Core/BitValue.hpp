#pragma once

//���������͵�λ���� ����ֵֻ�������õ�����(int, short, char..��)
template<class T>
class BitValue
{
public:
    enum BitValueDefine
    {
        ErrorValue = -1,        // ����ֵ
        NoneValue = 0,          // û��λֵ
        HaveValue = 1,          // ����λֵ
    };

    BitValue() : m_nValue(0) { }
    BitValue(T nValue) : m_nValue(nValue) { }

    void SetValue(T nValue)
    {
        m_nValue = nValue;
    }
    T GetValue() const
    {
        return m_nValue;
    }

    static int GetBitLength()
    {
        return sizeof(T) * 8;
    }

    // ��õ�һ��λֵ��0��λ����
    int GetFirstNoValueIndex()
    {
        for (int i = 0; i < GetBitLength(); ++i)
        {
            if ((m_nValue & (T(1) << i)) == NoneValue)
            {
                return i;
            }
        }

        return -1;  // 32λ����ֵ
    }

    T GetBitValue(unsigned char nIndex)         // �õ�ĳλ�ϵ�ֵ
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return ErrorValue;
        }

        return (m_nValue & (T(1) << nIndex));
    }

    void SetBitValue(unsigned char nIndex)        // ����ĳλ�ϵ�ֵ
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return;
        }

        m_nValue |= (T(1) << nIndex);
    }

    void ClearBitValue(unsigned char nIndex)      // ���ĳλ�ϵ�ֵ
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return;
        }

        m_nValue &= ~(T(1) << nIndex);
    }

    bool HaveBitValue(unsigned char nIndex)
    {
        return GetBitValue(nIndex) != NoneValue;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    static int GetFirstNoValueIndex(T nValue)
    {
        for (int i = 0; i < GetBitLength(); ++i)
        {
            if ((nValue & (T(1) << i)) == NoneValue)
            {
                return i;
            }
        }
        return -1;  // 32λ����ֵ
    }

    static T GetBitValue(T nValue, unsigned char nIndex)
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return ErrorValue;
        }

        return (nValue & (T(1) << nIndex));
    }

    static void SetBitValue(T& nValue, unsigned char nIndex)
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return;
        }

        nValue |= (T(1) << nIndex);
    }

    static void ClearBitValue(T& nValue, unsigned char nIndex)
    {
        if (nIndex < 0 || nIndex >= GetBitLength())
        {
            return;
        }

        nValue &= ~(T(1) << nIndex);
    }

    static bool HaveBitValue(T nValue, unsigned char nIndex)
    {
        return GetBitValue(nValue, nIndex) != NoneValue;
    }

private:
    T m_nValue;
};