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

#include "ofxOneEuroFilter.h"

// -----------------------------------------------------------------
ofxOneEuroFilter::ofxOneEuroFilter() :
	freq(60.0)
	,mincutoff(1.0)
	,beta_(0.0)
	,dcutoff(1.0)
	,x(alpha(mincutoff))
	,dx(alpha(dcutoff))
{}

ofxOneEuroFilter::ofxOneEuroFilter(double _freq, double _mincutoff, double _beta_, double _dcutoff) :
	x(alpha(_mincutoff))
	,dx(alpha(_dcutoff))
{
	// this also adjusts LowPassFilter alpha values
	setup(_freq, _mincutoff, _beta_, _dcutoff);
}


// -----------------------------------------------------------------
void  ofxOneEuroFilter::setup(double freq,
							  double mincutoff, double beta_, double dcutoff)
{
	setFrequency(freq) ;
	setMinCutoff(mincutoff) ;
	setBeta(beta_) ;
	setDerivateCutoff(dcutoff) ;
	lasttime = UndefinedTime ;
}


// -----------------------------------------------------------------
double ofxOneEuroFilter::filter(double value, TimeStamp timestamp) {
	// update the sampling frequency based on timestamps
	if (lasttime!=UndefinedTime && timestamp!=UndefinedTime)
		freq = 1.0 / (timestamp-lasttime) ;
	lasttime = timestamp ;
	// estimate the current variation per second
	double dvalue = x.hasLastRawValue() ? (value - x.lastRawValue())*freq : 0.0 ; // FIXME: 0.0 or value?
	double edvalue = dx.filterWithAlpha(dvalue, alpha(dcutoff)) ;
	// use it to update the cutoff frequency
	double cutoff = mincutoff + beta_*fabs(edvalue) ;
	// filter the given value
	return x.filterWithAlpha(value, alpha(cutoff)) ;
}




// -----------------------------------------------------------------
// privates
double ofxOneEuroFilter::alpha(double cutoff) {
	double te = 1.0 / freq ;
	double tau = 1.0 / (2*M_PI*cutoff) ;
	return 1.0 / (1.0 + tau/te) ;
}

void ofxOneEuroFilter::setFrequency(double f) {
	if (f<=0) return;
	freq = f ;
}

void ofxOneEuroFilter::setMinCutoff(double mc) {
	if (mc<=0) return;
	mincutoff = mc ;
	
	x.setAlpha(alpha(mincutoff));
}

void ofxOneEuroFilter::setBeta(double b) {
	beta_ = b ;
}

void ofxOneEuroFilter::setDerivateCutoff(double dc) {
	if (dc<=0) return;
	dcutoff = dc ;
	
	dx.setAlpha(alpha(dcutoff));
}