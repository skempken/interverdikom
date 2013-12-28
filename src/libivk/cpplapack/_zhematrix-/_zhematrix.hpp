//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision Hermitian Matrix Class
class _zhematrix
{
public:
  //// objects ////
  mutable long N; //!< matrix column or row size
  mutable std::complex<double>* Array; //!< 1D Array to store matrix data
  mutable std::complex<double>** Darray; //!< array of pointers of column head addresses
  
  //// constructor ////
  inline _zhematrix();
  inline _zhematrix(const _zhematrix&);
  inline ~_zhematrix(); //destructor
  
  //// io ////
  inline __zhecomplex operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zhematrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void complete() const;
  inline void destroy() const;
  
  //// calc ////
  inline friend _zhematrix t(const _zhematrix&);
  inline friend _zgematrix i(const _zhematrix&);
  
  //// unary ////
  inline friend const _zhematrix& operator+(const _zhematrix&);
  inline friend _zhematrix operator-(const _zhematrix&);
  
  //// + ////
  inline friend _zhematrix operator+(const  zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator+(const  zhematrix&, const _zhematrix&);
  inline friend _zhematrix operator+(const _zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator+(const _zhematrix&, const _zhematrix&);
  
  inline friend _zgematrix operator+(const _zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const _zhematrix&);
  
  inline friend _zgematrix operator+(const _zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const _zhematrix&);
  
  //// - ////
  inline friend _zhematrix operator-(const  zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator-(const  zhematrix&, const _zhematrix&);
  inline friend _zhematrix operator-(const _zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator-(const _zhematrix&, const _zhematrix&);
  
  inline friend _zgematrix operator-(const _zhematrix&, const  zgematrix&);  
  inline friend _zgematrix operator-(const _zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const _zhematrix&);
  
  inline friend _zgematrix operator-(const _zhematrix&, const  zgbmatrix&);  
  inline friend _zgematrix operator-(const _zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const _zhematrix&);
  
  //// * ////
  inline friend _zgematrix operator*(const _zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const _zhematrix&);
  
  inline friend _zgematrix operator*(const _zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const _zhematrix&);
  
  inline friend _zgematrix operator*(const _zhematrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const _zhematrix&);
  
  inline friend _zrovector operator*(const  zrovector&, const _zhematrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zhematrix&);
  inline friend _zcovector operator*(const _zhematrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zhematrix&, const _zcovector&);
  
  inline friend _zhematrix operator*(const  zhematrix&, const     double&);
  inline friend _zhematrix operator*(const _zhematrix&, const     double&);
  inline friend _zhematrix operator*(const     double&, const  zhematrix&);
  inline friend _zhematrix operator*(const     double&, const _zhematrix&);
  
  inline friend _zgematrix operator*(const _zhematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const std::complex<double>&, const _zhematrix&);
  //// / ////
  inline friend _zhematrix operator/(const  zhematrix&, const     double&);
  inline friend _zhematrix operator/(const _zhematrix&, const     double&);
  inline friend _zgematrix operator/(const _zhematrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
