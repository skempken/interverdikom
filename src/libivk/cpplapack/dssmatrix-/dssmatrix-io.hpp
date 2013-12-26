//=============================================================================
/*! operator() for const object */
inline double dssmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ return Array[c]; }
  }
  
  //// (i,j) component not found ////
  std::cerr << "[ERROR] dssmatrix::operator()(long, long)" << std::endl
            << "The required component is out of the matrix size."
            << std::endl
            << "Your input was (" << i << "," << j << ")." << std::endl;
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! put value with isListed check and volume cheack */
inline void dssmatrix::put(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::put(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::put(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){ 
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] dssmatrix::put(long&, long&, double&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=v;
  VOL++;
}

//=============================================================================
/*! put value without isListed check and volume cheack */
inline void dssmatrix::fput(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::fput(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::fput"
              << "(const long&, lconst ong&, const double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
  
  if(VOL==CAP){ 
    std::cerr << "[ERROR] dssmatrix::fput"
              << "(const long&, const long&, const double&)" << std::endl
              << "There is no free space to set a new entry." << std::endl;
    exit(1);
  }
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){
      std::cerr << "[ERROR] dssmatrix::fput"
                << "(const long&, const long&, const double&)" << std::endl
                << "The required component is already listed." << std::endl
                << "Your input was (" << i << "," << j << ")." << std::endl;
      exit(1);
    }
  }
#endif//CPPL_DEBUG
  
  Indx[VOL]=i;  Jndx[VOL]=j;  Array[VOL]=v;
  VOL++;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! add value with isListed check and volume cheack */
inline void dssmatrix::add(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::add(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::add(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]+=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] dssmatrix::add(long&, long&, double&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=v;
  VOL++;
}

//=============================================================================
/*! subtract value with isListed check and volume cheack */
inline void dssmatrix::sub(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::sub(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::sub(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]-=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] dssmatrix::sub(long&, long&, double&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=-v;
  VOL++;
}

//=============================================================================
/*! multiply value with isListed check and volume cheack */
inline void dssmatrix::mult(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::mult(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::mult(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]*=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  return;
}

//=============================================================================
/*! divide value with isListed check and volume cheack */
inline void dssmatrix::div(const long& i, const long& j, const double& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::div(const long&, const long&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::div(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]/=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  return;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! delete the entry of a component */
inline void dssmatrix::del(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::del(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::del(long&, long&, double&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){
      VOL--;
      Indx[c]=Indx[VOL];  Jndx[c]=Jndx[VOL];  Array[c]=Array[VOL];
      return;
    }
  }
  
  std::cerr << "[WARNING] dssmatrix::del(long&, long&, double&) "
            << "The required component was not listed. "
            << "Your input was (" << i << "," << j << ")." << std::endl;
}

//=============================================================================
/*! delete the entry of an element */
inline void dssmatrix::fdel(const long& c)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::fdel(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( c<0 || c>VOL ){
    std::cerr << "[ERROR] dssmatrix::fdel(const long&)" << std::endl
              << "The required element is out of the matrix volume."
              << std::endl
              << "Your input was (" << c << ")." << std::endl;
    exit(1);
  }
  
  std::cerr << "# [NOTE] dssmatrix::fdel(const long&) "
            << "The (" << Indx[c] << "," << Jndx[c]
            << ") component is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  
  VOL--;
  Indx[c]=Indx[VOL];  Jndx[c]=Jndx[VOL];  Array[c]=Array[VOL];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const dssmatrix&)"
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
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void dssmatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "dssmatrix" << " " << M << " " << N << " " << CAP << std::endl;
  for(long c=0; c<VOL; c++){
    s << Indx[c] << " " << Jndx[c] << " " << Array[c] << std::endl;
  }
  s.close();
}

//=============================================================================
inline void dssmatrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] dssmatrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "dssmatrix" ){
    std::cerr << "[ERROR] dssmatrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not dssmatrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> M >> N >> CAP;
  resize(M, N, CAP);
  
  long pos, tmp; 
  while(!s.eof() && VOL<CAP){
    s >> Indx[VOL] >> Jndx[VOL] >> Array[VOL];
    pos =s.tellg(); s >> tmp; s.seekg(pos);
    VOL++;
  }
  
  if(!s.eof()){
    std::cerr << "[ERROR] dssmatrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there are too many data components "
              << "over the context." << std::endl;
    exit(1);
  }
  s.close();
}
