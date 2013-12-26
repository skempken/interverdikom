//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision Sparse Matrix Class
class _zssmatrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable long CAP; //!< the length of data arrays
  mutable long VOL; //!< the number of non-zero components
  mutable std::complex<double>* Array; //!< 1D array to store non-zero matrix data
  mutable long* Indx; //!< 1D array to store the i-index of non-zero matrix components
  mutable long* Jndx; //!< 1D array to store the j-index of non-zero matrix components
  
  //// constructor ////
  inline _zssmatrix();
  inline _zssmatrix(const _zssmatrix&);
  inline ~_zssmatrix(); //destructor
  
  //// io ////
  inline std::complex<double> operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _zssmatrix&);
  inline void write(const char *) const;

  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _zssmatrix t(const zssmatrix&);
  inline friend void idamax(long&, long&, const zssmatrix&);
  inline friend std::complex<double> damax(const zssmatrix&);
  
  //// unary ////
  inline friend const _zssmatrix& operator+(const _zssmatrix&);
  inline friend _zssmatrix operator-(const _zssmatrix&);
  
  //// + ////
  inline friend _zssmatrix operator+(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator+(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator+(const _zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator+(const _zssmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator+(const _zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator+(const _zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator+(const _zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const _zssmatrix&);
  
  //// - ////
  inline friend _zssmatrix operator-(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator-(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator-(const _zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator-(const _zssmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator-(const _zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator-(const _zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator-(const _zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const _zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const _zssmatrix&);
  
  //// * ////
  inline friend _zssmatrix operator*(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator*(const _zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const _zssmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator*(const _zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const _zssmatrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator*(const _zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zssmatrix&);
  
  inline friend _zgematrix operator*(const _zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zssmatrix&);
  
  inline friend _zcovector operator*(const  zssmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zssmatrix&, const _zcovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const _zssmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zssmatrix&);
  
  inline friend _zssmatrix operator*(const  zssmatrix&, const     double&);
  inline friend _zssmatrix operator*(const _zssmatrix&, const     double&);
  inline friend _zssmatrix operator*(const     double&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const     double&, const _zssmatrix&);
  
  inline friend _zssmatrix operator*(const  zssmatrix&, const std::complex<double>&);
  inline friend _zssmatrix operator*(const _zssmatrix&, const std::complex<double>&);
  inline friend _zssmatrix operator*(const std::complex<double>&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const std::complex<double>&, const _zssmatrix&);
  
  //// / ////
  inline friend _zssmatrix operator/(const  zssmatrix&, const double&);
  inline friend _zssmatrix operator/(const _zssmatrix&, const double&);
  inline friend _zssmatrix operator/(const  zssmatrix&, const std::complex<double>&);
  inline friend _zssmatrix operator/(const _zssmatrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zssmatrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
