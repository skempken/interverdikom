//=============================================================================
/*! operator() for const object */
inline double _dssmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] _dssmatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ return Array[c]; }
  }

  return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long c;
  for(long i=0; i<mat.M; i++){
    for(long j=0; j<mat.N; j++){
      c=0;
      while(c<mat.VOL){
        if(mat.Indx[c]==i && mat.Jndx[c]==j){ break; }
        c++;
      }
      if(c!=mat.VOL){ s << mat.Array[c] << " "; }
      else{ s << "x "; }
    }
    s << std::endl;
  }
  
  mat.destroy();
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void _dssmatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "_dssmatrix" << " " << M << " " << N << " " << CAP << std::endl;
  for(long c=0; c<VOL; c++){
    s << Indx[c] << " " << Jndx[c] << " " << Array[c] << std::endl;
  }
  
  s.close();
  destroy();
}
