//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void dssmatrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG
  
  M =N =CAP =VOL=0;
  delete [] Array;  Array =NULL;
  delete [] Indx;  Indx =NULL;
  delete [] Jndx;  Jndx =NULL;
}

//=============================================================================
/*! change the matrix into a zero matrix */
inline void dssmatrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  VOL =0;
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void dssmatrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<VOL; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void dssmatrix::copy(const dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::copy(const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::copy(const dssmatrix&) "
            << "A dssmatrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  resize(mat.M, mat.N, mat.CAP);
  VOL =mat.VOL;
  dcopy_(VOL, mat.Array, 1, Array, 1);
  for(long i=0; i<VOL; i++){
    Indx[i] =mat.Indx[i];
    Jndx[i] =mat.Jndx[i];
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a dssmatrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void dssmatrix::shallow_copy(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::shallow_copy(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix:shallow_copy(const _dssmatrix&) "
            << "A dssmatrix at " << Array << " is going to be deleted, "
            << "and point at " << mat.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Indx;
  delete [] Jndx;
  M =mat.M;
  N =mat.N;
  CAP =mat.CAP;
  VOL =mat.VOL;
  Array =mat.Array;
  Indx =mat.Indx;
  Jndx =mat.Jndx;
}

//=============================================================================
/*! resize the matrix */
inline void dssmatrix::resize(const long& _m, const long& _n, const long& _c)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::resize(const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _c<0 ){
    std::cerr << "[ERROR] dssmatrix::resize"
              << "(const long&, const long&, const long&)"
              << std::endl
              << "Matrix sizes and the length of arrays "
              << "must be positive integers. " << std::endl
              << "Your input was (" << _m << "," << _n << "," << _c << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  delete [] Array;
  M =_m;
  N =_n;
  CAP =_c;
  VOL =0;
  Array =new double[CAP];
  Indx =new long[CAP];
  Jndx =new long[CAP];
}

//=============================================================================
/*! expand the matrix capacity */
inline void dssmatrix::expand(const long& dc)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::expand(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( dc<0 ){
    std::cerr << "[ERROR] dssmatrix::expand(const long&)" << std::endl
              << "The argument must be a positive integer. " << std::endl
              << "Your input was (" << dc << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  CAP+=dc;
  double* newArray(new double[CAP]);
  long *newIndx(new long[CAP]), *newJndx(new long[CAP]);
  
  for(int c=0; c<VOL; c++){
    newArray[c] =Array[c];
    newIndx[c] =Indx[c];
    newJndx[c] =Jndx[c];
  }
  
  delete [] Array;
  delete [] Indx;
  delete [] Jndx;
  Array =newArray;
  Indx =newIndx;
  Jndx =newJndx;
}

//=============================================================================
/*! check if the component is listed */
inline bool dssmatrix::isListed(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::isListed(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::isListed(const long&, const long&)"
              << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(int c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ return 1; }
  }
  
  return 0;
}


//=============================================================================
/*! return the element number of the component */
inline long dssmatrix::number(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::number(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dssmatrix::number(const long&, const long&)"
              << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ return c; }
  }
  
  return -1;
}


//=============================================================================
/*! swap two matrices */
inline void swap(dssmatrix& A, dssmatrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(dssmatrix&, dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_M(A.M), A_N(A.N), A_CAP(A.CAP), A_VOL(A.VOL);
  double* A_Array(A.Array);
  long *A_Indx(A.Indx), *A_Jndx(A.Jndx);
  A.M=B.M; A.N=B.N; A.CAP=B.CAP; A.VOL=B.VOL;
  A.Array=B.Array; A.Indx=B.Indx; A.Jndx=B.Jndx;
  B.M=A_M; B.N=A_N; B.CAP=A_CAP; B.VOL=A_VOL;
  B.Array=A_Array; B.Indx=A_Indx; B.Jndx=A_Jndx;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _dssmatrix _(dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _dssmatrix newmat;
  
  newmat.M =mat.M;
  newmat.N =mat.N;
  newmat.CAP =mat.CAP;
  newmat.VOL =mat.VOL;
  newmat.Array =mat.Array;
  newmat.Indx =mat.Indx;
  newmat.Jndx =mat.Jndx;
  
  mat.M =0;
  mat.N =0;
  mat.CAP =0;
  mat.VOL =0;
  mat.Array =NULL;
  mat.Indx =NULL;
  mat.Jndx =NULL;
  
  return newmat;
}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! health checkup */
inline void dssmatrix::checkup()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::checkup()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// CAP ////////
  if(CAP<0){
    std::cerr << "[ERROR] dssmatrix::checkup()" << std::endl
              << "The cap is not valid." << std::endl
              << "CAP was " << CAP << "." << std::endl;
    exit(1);
  }
  
  //////// VOL ////////
  if(VOL<0 || VOL>CAP){
    std::cerr << "[ERROR] dssmatrix::checkup()" << std::endl
              << "The vol is not valid." << std::endl
              << "VOL was " << VOL << "while CAP is " << CAP << "."
              << std::endl;
    exit(1);
  }
  
  //////// Elements ////////
  for(long c=0; c<VOL; c++){
    //// m bound ////
    if(Indx[c]<0 || Indx[c]>=M){
      std::cerr << "[ERROR] dssmatrix::checkup()" << std::endl
                << "The indx of the " << c
                << "th element is out of the matrix size." << std::endl
                << "Indx[" << c << "] was " << Indx[c] << "." << std::endl;
      exit(1);
    }

    //// n bound ////
    if(Jndx[c]<0 || Jndx[c]>=N){
      std::cerr << "[ERROR] dssmatrix::checkup()" << std::endl
                << "The jndx of the " << c
                << "th element is out of the matrix size." << std::endl
                << "Jndx[" << c << "] was " << Jndx[c] << "." << std::endl;
      exit(1);
    }
    
    //// double-listed ////
    for(long C=c+1; C<VOL; C++){
      if(Indx[c]==Indx[C] && Jndx[c]==Jndx[C]){
        std::cerr << "[ERROR] dssmatrix::checkup()" << std::endl
                  << "The (" << Indx[c] << ", " << Jndx[c]
                  << ") component is double-listed at the "
                  << c << "th and the" << C << "the elements."<< std::endl;
        exit(1);
      }
    }
  }
  
  //////// NOTE ////////
  std::cerr << "# [NOTE] dssmatrix::checkup() "
            << "This sparse matrix is fine." << std::endl;
}
