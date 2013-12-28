//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void zssmatrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zssmatrix::clear() "
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
inline void zssmatrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  VOL =0;
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void zssmatrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<VOL; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void zssmatrix::copy(const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::copy(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zssmatrix::copy(const zssmatrix&) "
            << "A zssmatrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  resize(mat.M, mat.N, mat.CAP);
  VOL =mat.VOL;
  zcopy_(VOL, mat.Array, 1, Array, 1);
  for(long i=0; i<VOL; i++){
    Indx[i] =mat.Indx[i];
    Jndx[i] =mat.Jndx[i];
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a zssmatrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void zssmatrix::shallow_copy(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::shallow_copy(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zssmatrix:shallow_copy(const _zssmatrix&) "
            << "A zssmatrix at " << Array << " is going to be deleted, "
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
inline void zssmatrix::resize(const long& _m, const long& _n, const long& _c)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::resize(const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _c<0 ){
    std::cerr << "[ERROR] zssmatrix::resize"
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
  Array =new std::complex<double>[CAP];
  Indx =new long[CAP];
  Jndx =new long[CAP];
}

//=============================================================================
/*! expand the matrix capacity */
inline void zssmatrix::expand(const long& dc)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::expand(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( dc<0 ){
    std::cerr << "[ERROR] zssmatrix::expand(const long&)" << std::endl
              << "The argument must be a positive integer. " << std::endl
              << "Your input was (" << dc << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG

  CAP+=dc;
  std::complex<double>* newArray(new std::complex<double>[CAP]);
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
inline bool zssmatrix::isListed(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::isListed(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::isListed(const long&, const long&)"
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
inline long zssmatrix::number(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::number(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::number(const long&, const long&)"
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
inline void swap(zssmatrix& A, zssmatrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zssmatrix&, zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_M(A.M), A_N(A.N), A_CAP(A.CAP), A_VOL(A.VOL);
  std::complex<double>* A_Array(A.Array);
  long *A_Indx(A.Indx), *A_Jndx(A.Jndx);
  A.M=B.M; A.N=B.N; A.CAP=B.CAP; A.VOL=B.VOL;
  A.Array=B.Array; A.Indx=B.Indx; A.Jndx=B.Jndx;
  B.M=A_M; B.N=A_N; B.CAP=A_CAP; B.VOL=A_VOL;
  B.Array=A_Array; B.Indx=A_Indx; B.Jndx=A_Jndx;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zssmatrix _(zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zssmatrix newmat;

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
inline void zssmatrix::checkup()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::checkup()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// CAP ////////
  if(CAP<0){
    std::cerr << "[ERROR] zssmatrix::checkup()" << std::endl
              << "The cap is not valid." << std::endl
              << "CAP was " << CAP << "." << std::endl;
    exit(1);
  }
  
  //////// VOL ////////
  if(VOL<0 || VOL==CAP){
    std::cerr << "[ERROR] zssmatrix::checkup()" << std::endl
              << "The vol is not valid." << std::endl
              << "VOL was " << VOL << "while CAP is " << CAP << "."
              << std::endl;
    exit(1);
  }
  
  //////// Elements ////////
  for(long c=0; c<VOL; c++){
    //// m bound ////
    if(Indx[c]<0 || Indx[c]>=M){
      std::cerr << "[ERROR] zssmatrix::checkup()" << std::endl
                << "The indx of the " << c
                << "th element is out of the matrix size." << std::endl
                << "Indx[" << c << "] was " << Indx[c] << "." << std::endl;
      exit(1);
    }

    //// n bound ////
    if(Jndx[c]<0 || Jndx[c]>=N){
      std::cerr << "[ERROR] zssmatrix::checkup()" << std::endl
                << "The jndx of the " << c
                << "th element is out of the matrix size." << std::endl
                << "Jndx[" << c << "] was " << Jndx[c] << "." << std::endl;
      exit(1);
    }
    
    //// std::complex<double>-listed ////
    for(long C=c+1; C<VOL; C++){
      if(Indx[c]==Indx[C] && Jndx[c]==Jndx[C]){
        std::cerr << "[ERROR] zssmatrix::checkup()" << std::endl
                  << "The (" << Indx[c] << ", " << Jndx[c]
                  << ") component is std::complex<double>-listed at the "
                  << c << "th and the" << C << "the elements."<< std::endl;
        exit(1);
      }
    }
  }
  
  //////// NOTE ////////
  std::cerr << "# [NOTE] zssmatrix::checkup() "
            << "This sparse matrix is fine." << std::endl;
}
