//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void dgematrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::clear() "
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
inline void dgematrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<M*N; i++){ Array[i] =0.0; }
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void dgematrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::identity()" << std::endl
              << "Only square matrix can be a identity matrix." << std::endl
              << "The matrix size was " << M << "x" << N << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<M*N; i++){ Array[i] =0.0; }
  for(long i=0; i<M; i++){ operator()(i,i) =1.0; }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void dgematrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<M*N; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void dgematrix::copy(const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::copy(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::copy(const dgematrix&) "
            << "A dgematrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  delete [] Array;
  Array =new double[mat.M*mat.N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  dcopy_(mat.M*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a dgematrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void dgematrix::shallow_copy(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::shallow_copy(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix:shallow_copy(const _dgematrix&) "
            << "A dgematrix at " << Array << " is going to be deleted, "
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
inline void dgematrix::resize(const long& _m, const long& _n)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::resize(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 ){
    std::cerr << "[ERROR] dgematrix::resize(const long&, const long&)"
              << std::endl
              << "Matrix sizes must be positive integers." << std::endl
              << "Your input was (" << _m << "," << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  M =_m;
  N =_n;
  delete [] Array;
  Array =new double[M*N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(dgematrix& A, dgematrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(dgematrix&, dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_m(A.M), A_n(A.N);
  double* A_array(A.Array);
  double** A_darray(A.Darray);
  A.M=B.M; A.N=B.N; A.Array=B.Array; A.Darray=B.Darray;
  B.M=A_m; B.N=A_n; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _dgematrix _(dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  _dgematrix newmat;
  
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
