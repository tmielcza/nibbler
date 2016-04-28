#include "plstream.h"

class x08 {
public:
	x08( int, char ** );
	void cmap1_init( int );

private:
	plstream			*pls;

	static const int	XPTS;
	static const int	YPTS;
	static int			ROTZ;
	static int			ROTY;
	static const char	*title[];
};

const int x08::XPTS = 10;
const int x08::YPTS = 10;

int x08::ROTZ = 60;
int x08::ROTY = 30;

const char    *x08::  title[] = { "#frNIBBLER" };

// cmap1_init1

// Initializes color map 1 in HLS space.
// Basic grayscale variation from half-dark (which makes more interesting
// looking plot compared to dark) to light.
// An interesting variation on this:
// s[1] = 1.0

void x08::cmap1_init( int gray )
{
	PLFLT i[] = {0.0, 1.0};
	PLFLT h[] = {2400, 0}; // blue -> green -> yellow -> red
	PLFLT l[] = {0.6, 0.6};
	PLFLT s[] = {0.8, 0.8};
	bool rev[] = {false, false};

	pls->scmap1n( 256 );
	pls->scmap1l( false, 2, i, h, l, s, rev );
}

x08::x08( int argc, char **argv )
{
	int k;
	const int LEVELS = 10;

	PLFLT     *x = new PLFLT[ XPTS ];
	PLFLT     *y = new PLFLT[ YPTS ];
	PLFLT     **z;
	PLFLT     *clevel = new PLFLT[LEVELS];
	PLFLT     dx      = 2. / (PLFLT) ( XPTS - 1 );
	PLFLT     dy      = 2. / (PLFLT) ( YPTS - 1 );

	PLFLT     zmin = 0, zmax = 10;

	pls = new plstream();
	// Set device
	pls->sdev("ntk");
	//pls->sdev("xwin");
    pls->init();

    pls->Alloc2dGrid( &z, XPTS, YPTS );

	for (int y = 0; y < XPTS; y++) {
		for (int x = 0; x < YPTS; x++) {
			z[y][x] = 5;
		}
	}
	z[3][3] = 6;
	z[3][4] = 6;
	z[3][5] = 6;
	z[3][6] = 6;
	for (int i = 0; i < XPTS; i++ ) {
		x[i] = -1. + (PLFLT) i * dx;
	}
	for (int i = 0; i < YPTS; i++ ) {
        y[i] = -1. + (PLFLT) i * dy;
	}
	for (int i = 0; i < LEVELS; i++ )
		clevel[i] = 1;

	pls->lightsource( 1., 1., 1. );

	pls->adv( 0 );
	pls->vpor( 0.0, 1.0, 0.0, 0.9 );
	pls->wind( -1.0, 1.0, -0.9, 1.1 );
	pls->col0( 3 );
	pls->mtex( "t", 1.0, 0.5, 0.5, title[k] );
	pls->col0( 1 );

	pls->w3d( 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, 1.0, zmin, zmax, ROTZ, ROTY);

	pls->box3( "bnstu", "x axis", 0.0, 0,
			   "bnstu", "y axis", 0.0, 0,
			   "bcdmnstuv", "z axis", 0.0, 0 );

	pls->col0( 2 );

	cmap1_init( 1 );
//	pls->surf3d( x, y, z, XPTS, YPTS, MAG_COLOR, NULL, 0 );
	pls->surf3d( x, y, z, XPTS, YPTS, MAG_COLOR | FACETED, NULL, 0 );
//	pls->surf3d( x, y, z, XPTS, YPTS, 0, NULL, 0 );
	/*
	pls->surf3d( x, y, z, XPTS, YPTS, MAG_COLOR, NULL, 0 );
	pls->surf3d( x, y, z, XPTS, YPTS, MAG_COLOR | FACETED, NULL, 0 );
	pls->surf3d( x, y, z, XPTS, YPTS, MAG_COLOR | SURF_CONT | BASE_CONT, clevel, LEVELS );
	*/

	pls->Free2dGrid( z, XPTS, YPTS );

	delete[] x;
	delete[] y;
	delete[] clevel;
	delete pls;
}

int main( int argc, char **argv )
{
	x08 *x = new x08( argc, argv );

	delete x;
}
