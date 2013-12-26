//=============================================================================
//! Complex Double-precision General Band Matrix Class
class zgbmatrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  long KL; //!< lower band width (NOT accessible)
  long KU; //!< upper band width (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store matrix data (NOT accessible)
  std::complex<double>** Darray; //!< array of pointers of column head addresses(NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  long const& kl; //!< lower band width (readable)
  long const& ku; //!< upper band width (readable)
  std::complex<double>* const& array; //!< 1D array to store matrix data (readable)
  std::complex<double>** const& darray; //!< array of pointers of column head addresses (readable)

  //// constructor ////
  inline zgbmatrix();
  inline zgbmatrix(const zgbmatrix&);
  inline zgbmatrix(const _zgbmatrix&);
  inline zgbmatrix(const long&, const long&, const long&, const long&);
  inline zgbmatrix(const char*);
  inline ~zgbmatrix(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&, const long&);
  inline std::complex<double> operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const std::complex<double>&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zgbmatrix&);
  inline void write(const char *) const;
  inline void read(const char *);
  
  //// misc ////
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const zgbmatrix&);
  inline void shallow_copy(const _zgbmatrix&);
  inline void resize(const long&, const long&, const long&, const long&);
  inline friend void swap(zgbmatrix&, zgbmatrix&);
  inline friend _zgbmatrix _(zgbmatrix&);
  
  //// calc ////
  inline friend _zgbmatrix t(const zgbmatrix&);
  inline friend _zgematrix i(const zgbmatrix&);
  inline friend _zgbmatrix conj(const zgbmatrix&);
  inline friend _zgbmatrix conjt(const zgbmatrix&);
  
  //// lapack ////
  inline long zgbsv(zgematrix&);
  inline long zgbsv(zcovector&);
  
  //// unary ////
  inline friend const zgbmatrix& operator+(const zgbmatrix&);
  inline friend _zgbmatrix operator-(const zgbmatrix&);
  
  //// operators with zgbmatrix ////
  inline zgbmatrix& operator=(const zgbmatrix&);
  inline zgbmatrix& operator+=(const zgbmatrix&);
  inline zgbmatrix& operator-=(const zgbmatrix&);
  inline zgbmatrix& operator*=(const zgbmatrix&);
  //// operators with _zgbmatrix ////
  inline zgbmatrix& operator=(const _zgbmatrix&);
  inline zgbmatrix& operator+=(const _zgbmatrix&);
  inline zgbmatrix& operator-=(const _zgbmatrix&);
  inline zgbmatrix& operator*=(const _zgbmatrix&);
  //// operators with double ////
  inline zgbmatrix& operator*=(const double&);
  inline zgbmatrix& operator/=(const double&);  
  //// operators with std::complex<double> ////
  inline zgbmatrix& operator*=(const std::complex<double>&);
  inline zgbmatrix& operator/=(const std::complex<double>&);
  
  //// + ////
  inline friend _zgbmatrix operator+(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator+(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator+(const _zgbmatrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const  zgbmatrix&);
  
  //// - ////
  inline friend _zgbmatrix operator-(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator-(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator-(const _zgbmatrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zgbmatrix&); 
  
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const _zhematrix&, const  zgbmatrix&); 
  
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const  zgbmatrix&); 
  
  //// * ////
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator*(const _zgbmatrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const  zgbmatrix&);
  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zssmatrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const  zgbmatrix&);
  
  inline friend _zcovector operator*(const  zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zgbmatrix&, const _zcovector&);
  inline friend _zrovector operator*(const  zrovector&, const  zgbmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zgbmatrix&);
  
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator*(const     double&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const std::complex<double>&);
  inline friend _zgbmatrix operator*(const  std::complex<double>&, const zgbmatrix&);
  
  //// / ////
  inline friend _zgbmatrix operator/(const  zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator/(const  zgbmatrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
