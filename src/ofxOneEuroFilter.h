/* OneEuroFilter
 *
 * original code by
 * Author: Nicolas Roussel (nicolas.roussel@inria.fr)
 *
 * from: http://www.lifl.fr/~casiez/1euro/
 *
 * openFrameworks addon ofxOneEuroFilter
 * Ingo Randolf
 *
 */

#pragma once

#include <cmath>
#include <stdexcept>

typedef double TimeStamp ; // in seconds

static const TimeStamp UndefinedTime = -1.0 ;


// -----------------------------------------------------------------
class LowPassFilter {
	
public:
	
	LowPassFilter(double alpha, double initval=0.0) {
		y = s = initval ;
		setAlpha(alpha) ;
		initialized = false ;
	}
	
	void setAlpha(double alpha) {
		if (alpha<=0.0 || alpha>1.0)
			throw std::range_error("alpha should be in (0.0., 1.0]") ;
		a = alpha ;
	}
	
	double filter(double value) {
		double result ;
		if (initialized)
			result = a*value + (1.0-a)*s ;
		else {
			result = value ;
			initialized = true ;
		}
		y = value ;
		s = result ;
		return result ;
	}
	
	double filterWithAlpha(double value, double alpha) {
		setAlpha(alpha) ;
		return filter(value) ;
	}
	
	bool hasLastRawValue(void) {
		return initialized ;
	}
	
	double lastRawValue(void) {
		return y ;
	}
	
	
private:
	
	double y, a, s ;
	bool initialized ;
	
};


// -----------------------------------------------------------------
class ofxOneEuroFilter {
	
public:
	
	ofxOneEuroFilter();	
	ofxOneEuroFilter(double freq,
				  double mincutoff=1.0, double beta_=0.0, double dcutoff=1.0);
	
	
	void setup(double freq,
				  double mincutoff=1.0, double beta_=0.0, double dcutoff=1.0);
	
	double filter(double value, TimeStamp timestamp=UndefinedTime);

	void setFrequency(double f);
	void setMinCutoff(double mc);
	void setBeta(double b);
	void setDerivateCutoff(double dc);

	
private:
	double alpha(double cutoff);
	
	double freq;
	double mincutoff;
	double beta_;
	double dcutoff;
	LowPassFilter x;
	LowPassFilter dx;
	TimeStamp lasttime;
};