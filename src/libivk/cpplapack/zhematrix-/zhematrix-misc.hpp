//=============================================================================
/*! complete the upper-right components */
inline void zhematrix::complete() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::complete() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){
    for(long j=0; j<i; j++){
      Darray[i][j] =std::conj(Darray[j][i]);
    }    
#ifdef  CPPL_DEBUG
    if(std::fabs(std::imag(operator()(i,i))) > CPPL_EPS){
      std::cerr << "[WARNING] zhematrix::complete() const" << std::endl
                << "The " << i << "th diagonal component of the zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
}

//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void zhematrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::clear() "
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
inline void zhematrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){ for(long j=0; j<=i; j++){
    Array[i] =std::complex<double>(0.0,0.0);
  }}
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void zhematrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){
    for(long j=0; j<i; j++){
      Darray[j][i] =std::complex<double>(0.0,0.0);
    }
    Darray[i][i] =std::complex<double>(1.0,0.0);
  }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void zhematrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<N; i++){
    for(long j=0; j<=i; j++){
      Darray[j][i] =-Darray[j][i];
    }
  }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void zhematrix::copy(const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::copy(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::copy(const zhematrix&) "
            << "A zhematrix at " << Array << " is going to be deleted.";
#endif//CPPL_DEBUG
  
  N =mat.N;
  delete [] Array;
  Array =new std::complex<double>[N*N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
  
  zcopy_(mat.N*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << " Then, a COPY of a zhematrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void zhematrix::shallow_copy(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::shallow_copy(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix:shallow_copy(const _zhematrix&) "
            << "A zhematrix at " << Array << " is going to be deleted, "
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
inline void zhematrix::resize(const long& _n)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::resize(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _n<0 ){
    std::cerr << "[ERROR] zhematrix::resize(const long&, const long&)"
              << std::endl
              << "Matrix sizes must be positive integers." << std::endl
              << "Your input was (" << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  N =_n;
  delete [] Array;
  Array =new std::complex<double>[N*N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(zhematrix& A, zhematrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zhematrix&, zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_n(A.N);
  std::complex<double>* A_array(A.Array);
  std::complex<double>** A_darray(A.Darray);
  A.N=B.N; A.Array=B.Array; A.Darray=B.Darray;
  B.N=A_n; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zhematrix _(zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zhematrix newmat;

  newmat.N =mat.N;
  newmat.Array =mat.Array;
  newmat.Darray =mat.Darray;

  mat.N =0;
  mat.Array =NULL;
  mat.Darray =NULL;

  return newmat;
}
