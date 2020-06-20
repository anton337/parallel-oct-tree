
unsigned char * loadTexture(const char * filename, int width, int height ) {
    unsigned char * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    data = (unsigned char*)malloc( 4 * width * height + 10000 );

    // read texture data
    int ret = fread( data, 1, 4 * width * height + 10000 , file );
    cout << "ret=" << ret << " " << (4*width*height) << " " << ret - (4*width*height) << endl;
    int offset = ret - 4*width*height;
    fclose( file );

    return &data[0];
}

long WIDTH = 90;
long HEIGHT = 1099;
unsigned char * texDat = loadTexture("function/lucas_0.tif", WIDTH, HEIGHT);

/* textured cube */
template<typename T>
T isofunction(T x, T y, T z) {
  T dx = .15;
  T dy = .05;
  T dz = .85;
  int X = WIDTH*((-x+dx)/(2.0*dx));
  int Y = HEIGHT*((-z+dz)/(2.0*dz));
  if(X<0)X=0;
  if(Y<0)Y=0;
  if(X>=WIDTH)X=WIDTH-1;
  if(Y>=HEIGHT)Y=HEIGHT-1;
  int val = (int)texDat[4*(WIDTH*Y+X)];
  T v = val / 256.0;
  T D1 = x-dx;
  T D2 = -x-dx;
  T D3 = y-dy - 0.05*v;
  T D4 = -y-dy;
  T D5 = z-dz;
  T D6 = -z-dz;
  T M = max(max(D1,D2),max(max(D3,D4),max(D5,D6)));
  return M;
}

