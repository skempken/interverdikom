//=============================================================================
/*! complete the upper-right components */
inline void dsymatrix::complete() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::complete() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){
    for(long j=0; j<i; j++){
      Darray[i][j] =Darray[j][i];
    }
  }
}

//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void dsymatrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG
  
  N =0;
  delete [] Array;
  Array =NULL;
  delete [] Darray;
  Darray =NULL;
}

//=============================================================================
/*! change the matrix into a zero matrix */
inline void dsymatrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N*N; i++){ Array[i] =0.0; }
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void dsymatrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N*N; i++){ Array[i] =0.0; }
  for(long i=0; i<N; i++){ operator()(i,i) =1.0; }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void dsymatrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N*N; i++){ Array[i] =-Array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void dsymatrix::copy(const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::copy(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::copy(const dsymatrix&) "
            << "A dsymatrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  N =mat.N;
  delete [] Array;
  Array =new double[N*N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
  
  dcopy_(mat.N*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a dsymatrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void dsymatrix::shallow_copy(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::shallow_copy(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix:shallow_copy(const _dsymatrix&) "
            << "A dsymatrix at " << Array << " is going to be deleted, "
            << "and point at " << mat.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  N =mat.N;
  delete [] Array;
  Array =mat.Array;
  delete [] Darray;
  Darray =mat.Darray;
}

//=============================================================================
/*! resize the matrix */
inline void dsymatrix::resize(const long& _n)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _n<0 ){
    std::cerr << "[ERROR] dsymatrix::resize(const long&, const long&)"
              << std::endl
              << "Matrix sizes must be positive integers." << std::endl
              << "Your input was (" << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  N =_n;
  delete [] Array;
  Array =new double[N*N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(dsymatrix& A, dsymatrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(dsymatrix&, dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_n(A.N);
  double* A_array(A.Array);
  double** A_darray(A.Darray);
  A.N=B.N; A.Array=B.Array; A.Darray=B.Darray;
  B.N=A_n; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _dsymatrix _(dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _dsymatrix newmat;

  newmat.N =mat.N;
  newmat.Array =mat.Array;
  newmat.Darray =mat.Darray;

  mat.N =0;
  mat.Array =NULL;
  mat.Darray =NULL;
  
  return newmat;
}

