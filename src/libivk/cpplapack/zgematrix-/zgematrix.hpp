//=============================================================================
//! Complex Double-precision General Dence Matrix Class
class zgematrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store matrix data (NOT accessible)
  std::complex<double>** Darray; //!< array of pointers of column head addresses (NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  std::complex<double>* const& array; //!< 1D array to store matrix data (readable)
  std::complex<double>** const& darray; //!< array of pointers of column head addresses (readable)
  
  //// constructor ////
  inline zgematrix();
  inline zgematrix(const zgematrix&);
  inline zgematrix(const _zgematrix&);
  inline zgematrix(const zgbmatrix&);
  inline zgematrix(const _zgbmatrix&);
  inline zgematrix(const zhematrix&);
  inline zgematrix(const _zhematrix&);
  inline zgematrix(const zssmatrix&);
  inline zgematrix(const _zssmatrix&);
  inline zgematrix(const long&, const long&);
  inline zgematrix(const char*);
  inline ~zgematrix(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&, const long&);
  inline std::complex<double> operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const std::complex<double>&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zgematrix&);
  inline void write(const char *) const;
  inline void read(const char *);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const zgematrix&);
  inline void shallow_copy(const _zgematrix&);
  inline void resize(const long&, const long&);
  inline friend void swap(zgematrix&, zgematrix&);
  inline friend _zgematrix _(zgematrix&);
  
  //// calc ////
  inline friend _zgematrix t(const zgematrix&);
  inline friend _zgematrix i(const zgematrix&);
  inline friend _zgematrix conj(const zgematrix&);
  inline friend _zgematrix conjt(const zgematrix&);
  inline friend void idamax(long&, long&, const zgematrix&);
  inline friend std::complex<double> damax(const zgematrix&);
  
  //// lapack ////
  inline long zgesv(zgematrix&);
  inline long zgesv(zcovector&);
  inline long zgels(zgematrix&);
  inline long zgels(zcovector&);
  inline long zgels(zgematrix&, drovector&);
  inline long zgels(zcovector&, double&);
  inline long zgelss(zcovector&, dcovector&, long&, const double);
  inline long zgelss(zgematrix&, dcovector&, long&, const double);
  inline long zgeev(std::vector< std::complex<double> >&);
  inline long zgeev(std::vector< std::complex<double> >&, 
                    std::vector<zcovector>&);
  inline long zgeev(std::vector< std::complex<double> >&,
                    std::vector<zrovector>&);
  //inline long zgegv()
  inline long zgesvd(dcovector&, zgematrix&, zgematrix&);
  
  //// unary ////
  inline friend const zgematrix& operator+(const zgematrix&);
  inline friend _zgematrix operator-(const zgematrix&);
  
  //// operators with zgematrix ////
  inline zgematrix& operator=(const zgematrix&);
  inline zgematrix& operator+=(const zgematrix&);
  inline zgematrix& operator-=(const zgematrix&);
  inline zgematrix& operator*=(const zgematrix&);
  //// operators with _zgematrix ////
  inline zgematrix& operator=(const _zgematrix&);
  inline zgematrix& operator+=(const _zgematrix&);
  inline zgematrix& operator-=(const _zgematrix&);
  inline zgematrix& operator*=(const _zgematrix&);
  //// operators with zgbmatrix ////
  inline zgematrix& operator=(const zgbmatrix&);
  inline zgematrix& operator+=(const zgbmatrix&);
  inline zgematrix& operator-=(const zgbmatrix&);
  inline zgematrix& operator*=(const zgbmatrix&);
  //// operators with _zgbmatrix ////
  inline zgematrix& operator=(const _zgbmatrix&);
  inline zgematrix& operator+=(const _zgbmatrix&);
  inline zgematrix& operator-=(const _zgbmatrix&);
  inline zgematrix& operator*=(const _zgbmatrix&);
  //// operators with zhematrix ////
  inline zgematrix& operator=(const zhematrix& mat);
  inline zgematrix& operator+=(const zhematrix& mat);
  inline zgematrix& operator-=(const zhematrix& mat);
  inline zgematrix& operator*=(const zhematrix& mat);
  //// operators with _zhematrix ////
  inline zgematrix& operator=(const _zhematrix& mat);
  inline zgematrix& operator+=(const _zhematrix& mat);
  inline zgematrix& operator-=(const _zhematrix& mat);
  inline zgematrix& operator*=(const _zhematrix& mat);
  //// operators with double ////
  inline zgematrix& operator*=(const double&);
  inline zgematrix& operator/=(const double&);
  //// operators with std::complex<double> ////
  inline zgematrix& operator*=(const std::complex<double>&);
  inline zgematrix& operator/=(const std::complex<double>&);

  //// + ////
  inline friend _zgematrix operator+(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zgematrix&);
  
  inline friend _zgematrix operator+(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zgematrix&);
  
  inline friend _zgematrix operator+(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const  zgematrix&);
  
  inline friend _zgematrix operator+(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zssmatrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zssmatrix&, const  zgematrix&);

  //// - ////
  inline friend _zgematrix operator-(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zgematrix&);
  
  inline friend _zgematrix operator-(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zgematrix&);
  
  inline friend _zgematrix operator-(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zhematrix&, const  zgematrix&);
  
  inline friend _zgematrix operator-(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zssmatrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zssmatrix&, const  zgematrix&);
  
  //// * ////
  inline friend _zgematrix operator*(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zgematrix&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zgbmatrix&);  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const  zgematrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zhematrix&);

  inline friend _zgematrix operator*(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zssmatrix&);
  
  inline friend _zcovector operator*(const  zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zgematrix&, const _zcovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const  zgematrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zgematrix&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const     double&);
  inline friend _zgematrix operator*(const     double&, const  zgematrix&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const std::complex<double>&, const  zgematrix&);
  
  //// / ////
  inline friend _zgematrix operator/(const  zgematrix&, const     double&);
  inline friend _zgematrix operator/(const  zgematrix&, const std::complex<double>&);

  //// friend classes ////
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zssmatrix;
  friend class _zssmatrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
