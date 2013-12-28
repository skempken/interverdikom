//=============================================================================
//! Complex Double-precision Hermitian Matrix Class [L-type (UPLO=L) Strage]
/*! The imaginary part of every diagonal component is not referenced. */
class zhematrix
{
private:
  //// objects ////
  long N; //!< matrix column size or row size (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store matrix data (NOT accessible)
  std::complex<double>** Darray; //!< array of pointers of column head addresses (NOT accessible)
  
public:
  //// const references ////
  long const& n; //!< matrix column size or row size (readable)
  std::complex<double>* const& array; //!< 1D array to store matrix data (readable)
  std::complex<double>** const& darray; //!< array of pointers of column head addresses (readable)
  
  //// constructor ////
  inline zhematrix();
  inline zhematrix(const zhematrix&);
  inline zhematrix(const _zhematrix&);
  inline zhematrix(const zgbmatrix&);
  inline zhematrix(const _zgbmatrix&);
  inline zhematrix(const long&);
  inline zhematrix(const char*);
  inline ~zhematrix(); //destructor
  
  //// io ////
  inline __zhecomplex operator()(const long&, const long&);
  inline std::complex<double>  operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const std::complex<double>&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zhematrix&);
  inline void write(const char*) const;
  inline void read(const char*);
  
  //// misc ////
  inline void complete() const;
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const zhematrix&);
  inline void shallow_copy(const _zhematrix&);
  inline void resize(const long&);
  inline friend void swap(zhematrix&, zhematrix&);
  inline friend _zhematrix _(zhematrix&);
  
  //// calc ////
  inline friend _zhematrix t(const zhematrix&);
  inline friend _zgematrix i(const zhematrix&);
  inline friend _zhematrix conj(const zhematrix&);
  inline friend _zhematrix conjt(const zhematrix&);
  
  //// lapack ////
  inline long zhesv(zgematrix&);
  inline long zhesv(zcovector&);
  inline long zheev(std::vector<double>&, const bool&);
  inline long zheev(std::vector<double>&, std::vector<zcovector>&);
  inline long zheev(std::vector<double>&, std::vector<zrovector>&);
  
  //// unary ////
  inline friend const zhematrix& operator+(const zhematrix&);
  inline friend _zhematrix operator-(const zhematrix&);
  
  //// operators with zhematrix ////
  inline zhematrix& operator=(const zhematrix&);
  inline zhematrix& operator+=(const zhematrix&);
  inline zhematrix& operator-=(const zhematrix&);
  inline zhematrix& operator*=(const zhematrix&);
  //// operators with _zhematrix ////
  inline zhematrix& operator=(const _zhematrix&);
  inline zhematrix& operator+=(const _zhematrix&);
  inline zhematrix& operator-=(const _zhematrix&);
  inline zhematrix& operator*=(const _zhematrix&);
  //// operators with double ////
  inline zhematrix& operator*=(const double&);
  inline zhematrix& operator/=(const double&);
  
  //// + ////
  inline friend _zhematrix operator+(const  zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator+(const  zhematrix&, const _zhematrix&);
  inline friend _zhematrix operator+(const _zhematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator+(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator+(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zhematrix&);
  
  inline friend _zgematrix operator+(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const  zhematrix&);

  //// - ////
  inline friend _zhematrix operator-(const  zhematrix&, const  zhematrix&);
  inline friend _zhematrix operator-(const  zhematrix&, const _zhematrix&);
  inline friend _zhematrix operator-(const _zhematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator-(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator-(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zhematrix&);
  
  inline friend _zgematrix operator-(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const  zhematrix&);
  
  //// * ////
  inline friend _zgematrix operator*(const _zhematrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zhematrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const  zhematrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zssmatrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const  zhematrix&);
  
  inline friend _zcovector operator*(const  zhematrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zhematrix&, const _zcovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const  zhematrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zhematrix&);
  
  inline friend _zhematrix operator*(const  zhematrix&, const     double&);
  inline friend _zhematrix operator*(const     double&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const std::complex<double>&, const  zhematrix&);
  
  //// / ////
  inline friend _zhematrix operator/(const  zhematrix&, const     double&);
  inline friend _zgematrix operator/(const  zhematrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class _zhematrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
