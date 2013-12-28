//=============================================================================
/*! _zgbmatrix*_zcovector operator */
inline _zcovector operator*(const _zgbmatrix& mat, const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgbmatrix&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const _zgbmatrix&, const _zcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector newvec(mat.M);
  zgbmv_( 'N', mat.M, mat.N, mat.KL, mat.KU, std::complex<double>(1.0,0.0), mat.Array,
          mat.KL+mat.KU+1, vec.Array, 1, std::complex<double>(0.0,0.0), newvec.array, 1 );
  
  mat.destroy();
  vec.destroy();
  return _(newvec);
}
