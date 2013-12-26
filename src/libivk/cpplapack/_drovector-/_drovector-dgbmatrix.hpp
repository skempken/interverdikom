//=============================================================================
/*! _drovector*dgbmatrix operator */
inline _drovector operator*(const _drovector& vec, const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _drovector&, const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vec.L!=mat.M){
    std::cerr << "[ERROR] operator*(const _drovector&, const dgbmatrix&)"
              << std::endl
              << "These vector and matrix can not make a product."
              << std::endl
              << "Your input was (" << vec.L << ") * ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  drovector newvec(mat.N);
  dgbmv_( 'T', mat.M, mat.N, mat.KL, mat.KU, 1.0,
          mat.Array, mat.KL+mat.KU+1, vec.Array, 1, 0.0, newvec.array, 1 );
  
  vec.destroy();
  return _(newvec);
}
