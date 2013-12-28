//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void zgematrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG
  
  M =0;
  N =0;
  delete [] Array;
  Array =NULL;
  delete [] Darray;
  Darray =NULL;
}

//=============================================================================
/*! change the matrix into a zero matrix */
inline void zgematrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<M*N; i++){ Array[i] =std::complex<double>(0.0,0.0); }
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void zgematrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] zgematrix::identity()" << std::endl
              << "Only square matrix can be a identity matrix." << std::endl
              << "The matrix size was " << M << "x" << N << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i] =std::complex<double>(0.0,0.0); }
  for(long i=0; i<M; i++){ operator()(i,i) =std::complex<double>(1.0,0.0); }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void zgematrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<M*N; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void zgematrix::copy(const zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::copy(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::copy(const zgematrix&) "
            << "A zgematrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  delete [] Array;
  Array =new std::complex<double>[M*N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }

  zcopy_(mat.M*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a zgematrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void zgematrix::shallow_copy(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::shallow_copy(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix:shallow_copy(const _zgematrix&) "
            << "A zgematrix at " << Array << " is going to be deleted, "
            << "and point at " << mat.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  delete [] Array;
  Array =mat.Array;
  delete [] Darray;
  Darray =mat.Darray;
}

//=============================================================================
/*! resize the matrix */
inline void zgematrix::resize(const long& _m, const long& _n)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::resize(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 ){
    std::cerr << "[ERROR] zgematrix::resize(const long&, const long&)"
              << std::endl
              << "Matrix sizes must be positive integers." << std::endl
              << "Your input was (" << _m << "," << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  M =_m;
  N =_n;
  delete [] Array;
  Array =new std::complex<double>[M*N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(zgematrix& A, zgematrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zgematrix&, zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_m(A.M), A_n(A.N);
  std::complex<double>* A_array(A.Array);
  std::complex<double>** A_darray(A.Darray);
  A.M=B.M; A.N=B.N; A.Array=B.Array; A.Darray=B.Darray;
  B.M=A_m; B.N=A_n; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zgematrix _(zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zgematrix newmat;

  newmat.M =mat.M;
  newmat.N =mat.N;
  newmat.Array =mat.Array;
  newmat.Darray =mat.Darray;

  mat.M =0;
  mat.N =0;
  mat.Array =NULL;
  mat.Darray =NULL;

  return newmat;
}
