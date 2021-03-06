//=============================================================================
/*! _dgematrix*dcovector operator */
inline _dcovector operator*(const _dgematrix& mat, const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dgematrix&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const _dgematrix&, const dcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dcovector newvec(mat.M);
  dgemv_( 'N', mat.M, mat.N, 1.0, mat.Array, mat.M,
          vec.Array, 1, 0.0, newvec.array, 1 );
  
  mat.destroy();
  return _(newvec);
}
