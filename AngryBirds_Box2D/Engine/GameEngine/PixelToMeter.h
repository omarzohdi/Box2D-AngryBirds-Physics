#ifndef PIXEL_TO_METER
#define PIXEL_TO_METER


class UnitScale
{
public:

	static void Create( float scale )
	{
		UnitScale *pScale = UnitScale::privInstance();
		pScale->pixelToMeter = scale;
		pScale->invPixelToMeter = 1.0f / scale;
	}

	static float  getPixelToMeterRatio()
	{
		UnitScale *pScale = UnitScale::privInstance();
		return pScale->invPixelToMeter;
	}

	static float  getMeterToPixelRatio()
	{
		UnitScale *pScale = UnitScale::privInstance();
		return pScale->pixelToMeter;
	}

private:
	float pixelToMeter;
	float invPixelToMeter;

	static UnitScale *privInstance()
	{
		static UnitScale instance;
		return &instance;
	};

	UnitScale()
	{
		this->pixelToMeter = 1.0f;
		this->invPixelToMeter = 1.0f;
	}
};



class PixelToMeter
{
public:
	PixelToMeter( const float pixelPos)
	{
		this->pixel_pos = pixelPos;
	}

	operator float()
	{
		return this->pixel_pos * UnitScale::getPixelToMeterRatio();
	}

private:
	float pixel_pos;
};


class MeterToPixel
{
public:
	MeterToPixel( const float meterPos)
	{
		this->meter_pos = meterPos;
	}

	operator float()
	{
		return this->meter_pos * UnitScale::getMeterToPixelRatio();
	}

private:
	float meter_pos;
};


#endif