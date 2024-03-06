/* src/GLOW/iri90.f -- translated by f2c (version 20160102).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

union {
    struct {
	real hmf2, nmf2, hmf1;
    } _1;
    struct {
	real hmf2, xnmf2, hmf1;
    } _2;
} block1_;

#define block1_1 (block1_._1)
#define block1_2 (block1_._2)

union {
    struct {
	real umr;
    } _1;
    struct {
	real faktor;
    } _2;
    struct {
	real dtr;
    } _3;
} const_;

#define const_1 (const_._1)
#define const_2 (const_._2)
#define const_3 (const_._3)

struct {
    real b0, b1, c1;
} block2_;

#define block2_1 block2_

struct {
    real hz, t, hst, str;
} block3_;

#define block3_1 block3_

union {
    struct {
	real hme, nme, hef;
    } _1;
    struct {
	real hme, xnme, hef;
    } _2;
} block4_;

#define block4_1 (block4_._1)
#define block4_2 (block4_._2)

struct {
    logical night;
    real e[4];
} block5_;

#define block5_1 block5_

union {
    struct {
	real hmd, nmd, hdx;
    } _1;
    struct {
	real hmd, xnmd, hdx;
    } _2;
} block6_;

#define block6_1 (block6_._1)
#define block6_2 (block6_._2)

struct {
    real d1, xkk, fp30, fp3u, fp1, fp2;
} block7_;

#define block7_1 block7_

union {
    struct {
	real hs, tnhs, xsm[4], mm[5], dti[4];
	integer mxsm;
    } _1;
    struct {
	real hs, tnhs, xsm[4], mm[5], g[4];
	integer m;
    } _2;
} block8_;

#define block8_1 (block8_._1)
#define block8_2 (block8_._2)

union {
    struct {
	real xsm1, texos, tlbdh, sigma;
    } _1;
    struct {
	real xsm1, tex, tlbd, sig;
    } _2;
} blotn_;

#define blotn_1 (blotn_._1)
#define blotn_2 (blotn_._2)

union {
    struct {
	real ahh[7], ate1, stte[6], dte[5];
    } _1;
    struct {
	real ah[7], ate1, st[6], d__[5];
    } _2;
} blote_;

#define blote_1 (blote_._1)
#define blote_2 (blote_._2)

struct {
    real beta, eta, delta, zeta;
} blo10_;

#define blo10_1 blo10_

struct {
    real argmax;
} argexp_;

#define argexp_1 argexp_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static real c_b47 = 300.f;
static integer c__0 = 0;
static real c_b51 = 12.f;
static integer c__1976 = 1976;
static integer c__882 = 882;
static real c_b83 = 28.f;
static real c_b84 = 1.f;
static real c_b88 = 81.f;
static real c_b91 = .06f;
static real c_b99 = 4e8f;
static real c_b101 = 88.f;
static real c_b104 = .05f;
static real c_b107 = 4.6f;
static real c_b108 = 4.5f;
static real c_b111 = -11.5f;
static real c_b112 = -4.f;
static real c_b118 = .001f;
static real c_b147 = 0.f;
static doublereal c_b153 = 2.;
static real c_b154 = 1.5f;
static real c_b160 = 3.f;
static real c_b167 = 130.f;
static real c_b168 = 500.f;
static real c_b171 = .01f;
static integer c__12 = 12;
static integer c__4 = 4;
static integer c__2 = 2;
static real c_b193 = 10.f;
static real c_b205 = 394.5f;
static real c_b207 = 100.f;
static integer c__8 = 8;
static doublereal c_b235 = 10.;
static integer c__6 = 6;
static integer c__76 = 76;
static integer c__13 = 13;
static integer c__988 = 988;
static integer c__7 = 7;
static integer c__49 = 49;
static integer c__441 = 441;
static doublereal c_b289 = .25;
static doublereal c_b291 = .3704;
static doublereal c_b294 = 2.7;
static real c_b380 = 2.f;
static real c_b384 = .1f;
static real c_b385 = .15f;

/* Subroutine IRI90 */

/* Special-purpose version of IRI90 for use with the GLOW model. */
/* This is not the original IRI90. */

/* Adapted 7/93 from 10/91 version of IRIS12 by Stan Solomon. */
/* Replaces 3/92 adaptation of 12/90 version of IRIS12. */
/* Replaced height range and interval with array of heights ZKM */
/* Also supply number of heights NZ; unlimited number of heights allowed. */
/* Added DIRECT argument to specify location of CCIR and URSI files. */
/* Uses ASCII versions of CCIR and URSI files. */
/* Subroutine DFP splices directory and filename together. */
/* Accepts longitudes -180 to +180; maps internal longitudes 0-360. */
/* Added SAVE statements for volatile memory machines. */
/* Changed 'file not found' error to output message on unit 6 and stop. */
/* Changed call to IONCOM to use floating point variable ZMONTH. */
/* Note: JF(5)=.false. uses recommended (URSI) coefficients. */
/* Note: JF(4)=.false. uses recommended Gulyeava B0 coefficients. */
/* All other JF's usually should be .true. */

/* The following is the original comment from IRIS12: */

/* IRIS12.FOR ---------------------------------------- OCTOBER 1991 */

/* ***************************************************************** */
/* CHANGES FROM  IRIS11.FOR  TO   IRIS12.FOR: */
/*    - CIRA-1986 INSTEAD OF CIRA-1972 FOR NEUTRAL TEMPERATURE */
/*    - 10/30/91 VNER FOR NIGHTTIME LAY-VERSION:  ABS(..) */
/*    - 10/30/91 XNE(..) IN CASE OF LAY-VERSION */
/*    - 10/30/91 CHANGE SSIN=F/T TO IIQU=0,1,2 */
/*    - 10/30/91 Te > Ti > Tn ENFORCED IN FINAL PROFILE */
/*    - 10/30/91 SUB ALL NAMES WITH 6 OR MORE CHARACTERS */
/*    - 10/31/91 CORRECTED HF1 IN HST SEARCH:  NE(HF1)>NME */
/* ------------- inlcuded on diskette ------------------------------ */
/*    - 11/14/91 C1=0 IF NO F1-REGION */
/*    - 11/14/91 CORRECTED HHMIN AND HZ FOR LIN. APP. */
/*    -  1/28/92 RZ12=0 included */
/*    -  1/29/92 NEQV instead of NE between URSIF2 and URSIFO */
/*    -  5/ 1/92 CCIR and URSI input as in IRID12 */

/* ***************************************************************** */
/* ********* INTERNATIONAL REFERENCE IONOSPHERE (IRI). ************* */
/* ***************************************************************** */
/* ****************    OCTOBER 1991     **************************** */
/* ****************     SUBROUTINE      **************************** */
/* ***************************************************************** */


/* ----------------------------------------------------------------- */
/* INTERNATIONAL REFERENCE IONOSPHERE 1991 */

/* INPUT:  JMAG=0/1      GEODETIC/GEOMAGNETIC LATITUDE AND LONGITUDE */
/*         ALATI,ALONG   LATITUDE NORTH AND LONGITUDE EAST IN DEGREES */
/*         RZ12 (-COV)   12-MONTHS-RUNNING MEAN OF SOLAR SUNSPOT NUMBER */
/*                          (OR EQUIVALENT F10.7 SOLAR RADIO FLUX AS */
/*                          NEGATIVE NUMBER) */
/*         MMDD (-DDD)   DATE (OR DAY OF YEAR AS A NEGATIVE NUMBER) */
/*         DHOUR         LOCAL TIME (OR UNIVERSAL TIME + 25) IN DECIMAL */
/*                          HOURS */
/*         ZKM(NZ)       ALTITUDE PROFILE IN KM */
/*         NZ            NUMBER OF ALTITUDES */
/*         JF(1:12)      TRUE/FALSE FLAGS FOR SEVERAL OPTIONS */
/*          JF(1)=.TRUE.[.FALSE.]   ELECTRON DENSITY IS [NOT] CALCULATED */
/*          JF(2)=T[F]    TEMPERATURES ARE [NOT] CALCULATED */
/*          JF(3)=T[F]    ION COMPOSITION IS [NOT] CALCULATED */
/*          JF(4)=T[F]    B0 FROM TABLE [FROM GULYEAVA 1987] */
/*          JF(5)=T[F]    F2 PEAK FROM CCIR [FROM URSI] */
/*          JF(6)=T[F]    ION COMP. STANDARD [DANILOV-YAICHNIKOV-1985] */
/*          JF(7)=T[F]    STAND. IRI TOPSIDE [IRI-79] */
/*          JF(8)=T[F]    NMF2 PEAK MODEL [INPUT VALUES] */
/*          JF(9)=T[F]    HMF2 PEAK MODEL [INPUT VALUES] */
/*          JF(10)=T[F]   TE MODEL [TE-NE MODEL WITH NE INPUT] */
/*          JF(11)=T[F]   NE STANDARD [LAY-FUNCTIONS VERSION] */
/*          JF(12)=T[F]   MESSAGE ARE WRITTEN TO /dev/null [stderr] */

/*  JF(1:11)=.TRUE. GENERATES THE STANDARD IRI-90 PARAMETERS. */
/*  IF YOU SET JF(8)=.FALSE., THAN YOU HAVE TO PROVIDE THE F2 PEAK */
/*  NMF2/M-3 OR FOF2/MHZ IN OARR(1). SIMILARLY, IF YOU SET JF(9)= */
/*  .FALSE., THAN YOU HAVE TO PROVIDE THE F2 PEAK HEIGHT HMF2/KM IN */
/*  OARR(2). IF YOU SET JF(10)=.FALSE., THAN YOU HAVE TO PROVIDE THE */
/*  ELECTRON DENSITY IN M-3 AT 300KM AND/OR 400KM AND/OR 600KM IN */
/*  OARR(3), OARR(4), AND OARR(5). IF YOU WANT TO USE THIS OPTION AT */
/*  ONLY ONE OF THE THREE ALTITUDES, THAN SET THE DENSITIES AT THE */
/*  OTHER TWO TO ZERO. */

/*  OUTPUT:  OUTF(1:10,1:50)   IRI PROFILES */
/*              OUTF(1,*)  ELECTRON DENSITY/M-3 */
/*              OUTF(2,*)  NEUTRAL TEMPERATURE/K */
/*              OUTF(3,*)  ION TEMPERATURE/K */
/*              OUTF(4,*)  ELECTRON TEMPERATURE/K */
/*              OUTF(5,*)  PERCENTAGE OF O+ IONS IN % */
/*              OUTF(6,*)  PERCENTAGE OF H+ IONS IN % */
/*              OUTF(7,*)  PERCENTAGE OF HE+ IONS IN % */
/*              OUTF(8,*)  PERCENTAGE OF O2+ IONS IN % */
/*              OUTF(9,*)  PERCENTAGE OF NO+ IONS IN % */
/*                 AND, IF JF(6)=.FALSE.: */
/*              OUTF(10,*)  PERCENTAGE OF CLUSTER IONS IN % */
/*              OUTF(11,*)  PERCENTAGE OF N+ IONS IN % */

/*            OARR(1:30)   ADDITIONAL OUTPUT PARAMETERS */
/*              OARR(1) = NMF2/M-3        OARR(2) = HMF2/KM */
/*              OARR(3) = NMF1/M-3        OARR(4) = HMF1/KM */
/*              OARR(5) = NME/M-3         OARR(6) = HME/KM */
/*              OARR(7) = NMD/M-3         OARR(8) = HMD/KM */
/*              OARR(9) = HHALF/KM        OARR(10) = B0/KM */
/*              OARR(11) =VALLEY-BASE/M-3 OARR(12) = VALLEY-TOP/KM */
/*              OARR(13) = TE-PEAK/K      OARR(14) = TE-PEAK HEIGHT/KM */
/*              OARR(15) = TE-MOD(300KM)  OARR(16) = TE-MOD(400KM)/K */
/*              OARR(17) = TE-MOD(600KM)  OARR(18) = TE-MOD(1400KM)/K */
/*              OARR(19) = TE-MOD(3000KM) OARR(20) = TE(120KM)=TN=TI/K */
/*              OARR(21) = TI-MOD(430KM)  OARR(22) = X/KM, WHERE TE=TI */
/*              OARR(23) = SOLAR ZENITH ANGLE/DEG */
/*              OARR(24) = SUN DECLINATION/DEG */
/*              OARR(25) = DIP */
/* 	       OARR(26) = DIP LATITUDE */
/*              OARR(27) = MODIFIED DIP LATITUDE */
/*              OARR(28:30) FREE */
/* ------------------------------------------------------------------- */
/* *** THIS PROGRAM PRODUCES PROFILES OF                         *** */
/* ***      ELECTRON DENSITY                                     *** */
/* ***      NEUTRAL TEMPERATURE (CIRA 86)                        *** */
/* ***      ELECTRON TEMPERATURE                                 *** */
/* ***      ION TEMPERATURE                                      *** */
/* ***      RELATIVE PERCENTAGE DENSITIES OF THE IONS            *** */
/* ***           ATOMIC OXYGEN, HYDROGEN, HELIUM,                *** */
/* ***           MOLECULAR OXYGEN AND NITROGEN OXYD (NO+)        *** */
/* ***************************************************************** */
/* *** THE ALTITUDE LIMITS ARE:  LOWER (DAY/NIGHT)  UPPER        *** */
/* ***     ELECTRON DENSITY         60/80 KM       1000 KM       *** */
/* ***     TEMPERATURES              120 KM        3000 KM       *** */
/* ***     ION DENSITIES             100 KM        1000 KM       *** */
/* ***************************************************************** */
/* *     --------------------ADDRESSES------------------------     * */
/* *     I  PROF. K. RAWER              DR. D. BILITZA       I     * */
/* *     I  HERRENSTR. 43               GSFC/NSSDC CODE 633  I     * */
/* *     I  D-7801 MARCH                GREENBELT MD 20771   I     * */
/* *     I  F.R.G.                      USA                  I     * */
/* *     -----------------------------------------------------     * */
/* ***************************************************************** */
/* ***************************************************************** */
/* ***************************************************************** */
/* *********       ALL ANGLES ARE IN DEGREE           ************** */
/* *********       ALL DENSITIES ARE IN M-3           ************** */
/* *********       ALL ALTITUDES ARE IN KM            ************** */
/* *********     ALL TEMPERATURES ARE IN KELVIN       ************** */
/* *********     ALL TIMES ARE IN DECIMAL HOURS       ************** */
/* ***************************************************************** */
/* ********************  OPTIONS  ********************************** */
/* ***************************************************************** */
/* * FOR HMF2=0 OR FOF2=0 THE F2 PEAK VALUES ARE CALCULATED WITH   * */
/* * THE CCIR OR URSI MODELS. THE CCIR COEFFICIENT SET FOR THE     * */
/* * MONTH "mm" IS EXPECTED IN THE BINARY FILE "CCIRmm.BIN" AND    * */
/* * THE URSI SET IN "URSImm.BIN". IF YOU USE THE ASCII CODED      * */
/* * FILES "CCIRmm.ASC", YOU HAVE TO INCORPORATE THE CHANGES       * */
/* * INDICTED IN PROGRAM SECTION ENTITLED "READ CCIR COEFFICIENT   * */
/* * SET FOR CHOSEN MONTH."                                        * */
/* ***************************************************************** */
/* ***************************************************************** */
/* ***************************************************************** */

/* Subroutine */ int iri90_(logical *jf, integer *jmag, real *alati, real *
	along, real *rz12, integer *mmdd, real *dhour, real *zkm, integer *nz,
	 char *direct, real *outf, real *oarr, ftnlen direct_len)
{
    /* Initialized data */

    static real hoa[3] = { 300.f,400.f,600.f };
    static real xnar[3] = { 0.f,0.f,0.f };
    static real xdels[4] = { 5.f,5.f,5.f,10.f };
    static real dnds[4] = { .016f,.01f,.016f,.016f };
    static integer ddo[4] = { 9,5,5,25 };
    static integer do2[2] = { 5,5 };
    static real b0b1[5] = { .755566f,.778596f,.797332f,.812928f,.826146f };
    static integer icalls = 0;

    /* Format strings */
    static char fmt_104[] = "(\002ccir\002,i2,\002.asc\002)";
    static char fmt_4689[] = "(4e15.8)";
    static char fmt_1144[] = "(\002ursi\002,i2,\002.asc\002)";
    static char fmt_650[] = "(1x,\002*NE* E-REGION VALLEY CAN NOT BE MODEL"
	    "LED\002)";
    static char fmt_11[] = "(1x,\002*NE* HMF1 IS NOT EVALUATED BY THE FUNCTI"
	    "ON XE2\002)";
    static char fmt_902[] = "(6x,\002CORR.: B1(OLD)=\002,f4.1,\002 B1(NEW)"
	    "=\002,f4.1)";
    static char fmt_9269[] = "(1x,\002CORR.: NO F1 REGION, B1=3, C1=0.0\002)";
    static char fmt_100[] = "(1x,\002*NE* HST IS NOT EVALUATED BY THE FUNCTI"
	    "ON XE3\002)";
    static char fmt_901[] = "(6x,\002CORR.: LIN. APP. BETWEEN HZ=\002,f5.1"
	    ",\002 AND HEF=\002,f5.1)";
    static char fmt_7733[] = "(\002*NE* LAY amplitudes found with 2nd choice"
	    " of HXL(1).\002)";
    static char fmt_7722[] = "(\002*NE* LAY amplitudes could not be found"
	    ".\002)";

    /* System generated locals */
    integer i__1;
    real r__1, r__2;
    doublereal d__1, d__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    double atan(doublereal), log(doublereal);
    integer f_open(olist *);
    double sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double tan(doublereal), exp(doublereal);
    integer s_wsfi(icilist *), do_fio(integer *, char *, ftnlen), e_wsfi(void)
	    , s_rsfe(cilist *), e_rsfe(void), f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double cos(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void);
    double pow_dd(doublereal *, doublereal *), r_sign(real *, real *);

    /* Local variables */
    static char filename[1*10];
    static real d__, f[3], h__;
    static integer i__, j, k, l;
    static real r__, x, y, z__, f2[1976]	/* was [13][76][2] */, z1, z2,
	     z3;
    static integer ki, kk;
    static real ho[4], rg, mo[5];
    static logical dy;
    static real ex;
    extern doublereal ti_(real *), xe_(real *), tn_(real *, real *, real *, 
	    real *);
    static real ut, ff0[988];
    static integer ib1;
    static real hf1, fm3[882]	/* was [9][49][2] */, ho2[2], h0o, mo2[3];
    extern doublereal xe2_(real *), xe3_(real *);
    static real xm0[441], rr2, rr1, ex1, xf1, ti1, dec, deh, ate[7], tea[6], 
	    amp[4], rif[4], scl[4], rgo, cov;
    extern /* Subroutine */ int ggm_(integer *, real *, real *, real *, real *
	    );
    static real hxl[4], xma;
    static logical ext;
    static real yma, zma, bet, dip, xhi, sax, foe, sux;
    extern /* Subroutine */ int dfp_(char *, char *, char *, ftnlen, ftnlen, 
	    ftnlen);
    static real flu;
    extern /* Subroutine */ int tal_(real *, real *, real *, real *, logical *
	    , real *);
    static real xdx, hta, hte, sec, ett, tet, fof2, eta1, fof1, ten, nmf1, 
	    tid1, tn120, pf1o[12], pg1o[80], pg2o[32], pg3o[80], pf2o[4], 
	    pf3o[12], cos2, xe2h, xe3h, ted1, hv1r, hv2r, tin1, ten1, tnn1, 
	    ti13, ti50, tex, tix, ho05;
    extern doublereal xen_(real *, real *, real *, real *, integer *, real *, 
	    real *, real *);
    static real tnh, tih, teh, rox, rhx, rnx, ro2x, dela, hnea;
    extern /* Subroutine */ int teba_(real *, real *, integer *, real *);
    static real hnee;
    extern /* Subroutine */ int moda_(integer *, integer *, integer *, 
	    integer *);
    static real dell;
    extern doublereal tede_(real *, real *, real *);
    static integer iday;
    static real lati, dion[7];
    static char path[1*1024];
    static real mlat;
    static logical old79;
    static real covg, xm3000;
    static logical tcon[3];
    extern /* Subroutine */ int soco_(integer *, real *, real *, real *, real 
	    *, real *, real *, real *);
    static real epin, seax, grat, xdel, hour;
    extern doublereal hpol_(real *, real *, real *, real *, real *, real *, 
	    real *);
    static real vner, dxdx, alg100;
    static integer iiqu;
    static real rrrr;
    extern doublereal elte_(real *);
    static real hnia, hnie, afof2, ahmf2;
    extern /* Subroutine */ int sufe_(real *, real *, integer *, real *);
    static real zzz1, delx, xtts;
    extern doublereal rpid_(real *, real *, real *, integer *, real *, 
	    integer *, real *);
    static logical f1reg;
    static real alog2, hhmf2, rhex, hmf1m;
    static logical gulb0;
    static real rnox;
    extern doublereal rdno_(real *, real *, real *, real *, real *), b0pol_(
	    real *, real *, real *, integer *, real *, real *);
    static real nobo2, pnmf1, yfof2, tn1ni, yoh0o;
    extern /* Subroutine */ int f2out_(real *, real *, real *, real *, real *,
	     real *, real *, real *);
    static real stte1, stte2, elede, ymo2z, hhalf, aldo21, hdeep, magbr, 
	    dlndh;
    extern /* Subroutine */ int cira86_(integer *, real *, real *, real *, 
	    real *, real *, real *, real *, real *), rdhhe_(real *, real *, 
	    real *, real *, real *, real *, real *, real *);
    extern doublereal xmded_(real *, real *, real *);
    static logical noden;
    extern doublereal teder_(real *);
    static real depth, rathh, hhmin, longi, modip, secni, mlong;
    static integer daynr;
    static real signi, width;
    static logical notem, noion;
    static integer jxnar, month;
    static real tlbdn;
    static logical botto;
    extern /* Subroutine */ int rogul_(integer *, real *, real *, real *);
    static real texni, hmaxd, hmaxn, xnehz, tmaxd;
    static logical topsi;
    static real tmaxn;
    extern doublereal dtndh_(real *, real *, real *, real *);
    static real xteti, xxmin;
    extern doublereal fof1ed_(real *, real *, real *), hmf2ed_(real *, real *,
	     real *, real *);
    extern /* Subroutine */ int regfa1_(real *, real *, real *, real *, real *
	    , real *, E_fp, logical *, real *);
    static integer msumo;
    static real hfixo, ymaxx, yo2h0o, b0cnew;
    static logical fof2in, hmf2in;
    static real tnahh2;
    extern /* Subroutine */ int koefp1_(real *), koefp2_(real *), koefp3_(
	    real *);
    static real sunde1, hfixo2;
    static logical ursif2;
    static real rdo2mx, heibeg;
    extern /* Subroutine */ int fieldg_(real *, real *, real *, real *, real *
	    , real *, real *, real *, real *, real *);
    extern doublereal foeedi_(real *, real *, real *, real *);
    static real heiend;
    static integer iregfa;
    static real dndhbr;
    static integer seaday;
    static real abslat, absmdp, absmbr, tnahhi;
    static logical belowe, schalt;
    static integer iuccir;
    static real sundec, absmlt, diplat, height;
    extern /* Subroutine */ int inilay_(logical *, real *, real *, real *, 
	    real *, real *, real *, real *, real *, real *, real *, real *, 
	    real *, real *, integer *), ioncom_(real *, real *, real *, real *
	    , real *, real *);
    static integer season;
    static logical teneop;
    static real rdomax;
    extern doublereal epstep_(real *, real *, real *, real *, real *);
    static logical layver;
    static integer stderr, montho, monito, istart;
    static logical ursifo;
    static integer konsol, nseson;
    static real xhinon, saxnon, rclust, zmonth;
    static integer stdout;
    static real suxnon;

    /* Fortran I/O blocks */
    static cilist io___35 = { 0, 0, 0, 0, 0 };
    static cilist io___36 = { 0, 0, 0, 0, 0 };
    static cilist io___37 = { 0, 0, 0, 0, 0 };
    static cilist io___38 = { 0, 0, 0, 0, 0 };
    static cilist io___39 = { 0, 0, 0, 0, 0 };
    static cilist io___40 = { 0, 0, 0, 0, 0 };
    static cilist io___41 = { 0, 0, 0, 0, 0 };
    static cilist io___42 = { 0, 0, 0, 0, 0 };
    static cilist io___43 = { 0, 0, 0, 0, 0 };
    static cilist io___44 = { 0, 0, 0, 0, 0 };
    static icilist io___90 = { 0, filename, 0, fmt_104, 1, 10 };
    static cilist io___92 = { 0, 0, 0, fmt_4689, 0 };
    static icilist io___95 = { 0, filename, 0, fmt_1144, 1, 10 };
    static cilist io___96 = { 0, 0, 0, fmt_4689, 0 };
    static cilist io___97 = { 0, 0, 0, 0, 0 };
    static cilist io___134 = { 0, 0, 0, fmt_650, 0 };
    static cilist io___142 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___144 = { 0, 0, 0, fmt_902, 0 };
    static cilist io___146 = { 0, 0, 0, fmt_9269, 0 };
    static cilist io___156 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___158 = { 0, 0, 0, fmt_901, 0 };
    static cilist io___168 = { 0, 0, 0, fmt_7733, 0 };
    static cilist io___169 = { 0, 0, 0, fmt_7722, 0 };


/* use, intrinsic :: iso_fortran_env, only: stdout=>output_unit, */
/*      &  stderr=>error_unit */
/* implicit none */
    /* Parameter adjustments */
    --jf;
    outf -= 12;
    --zkm;
    --direct;
    --oarr;

    /* Function Body */

    stdout = 6;
    stderr = 0;

/* PROGAM CONSTANTS */

    ++icalls;
    hhalf = 0.f;
/*       write(6,"('Enter iri90: icalls=',i4,' jf=',12l2,' jmax=',i4, */
/*    |    ' alati=',f8.2,' along=',f8.2)") */
/*    |    icalls,jf,jmax,alati,along */
/*       write(6,"('rz12=',f8.2,' mmdd=',i4,' dhour=',f8.2,' nz=',i4)") */
/*    |    rz12,mmdd,dhour,nz */
/*       write(6,"('DIRECT (file path)=',a)") direct */
/*       write(6,"('zkm=',/,(8f9.2))") zkm */
    argexp_1.argmax = 88.f;
    const_1.umr = atan(1.f) * 4.f / 180.f;
    alog2 = log(2.f);
    alg100 = log(100.f);
    istart = 1;
    heibeg = zkm[1];
    heiend = zkm[*nz];

/* Code inserted to aleviate block data problem for PC version. */
/* Thus avoiding DATA statement with parameters from COMMON block. */

    blote_1.ahh[0] = 120.f;
    blote_1.ahh[1] = 0.f;
    blote_1.ahh[2] = 300.f;
    blote_1.ahh[3] = 400.f;
    blote_1.ahh[4] = 600.f;
    blote_1.ahh[5] = 1400.f;
    blote_1.ahh[6] = 3e3f;
    blote_1.dte[0] = 5.f;
    blote_1.dte[1] = 5.f;
    blote_1.dte[2] = 10.f;
    blote_1.dte[3] = 20.f;
    blote_1.dte[4] = 20.f;
    block8_1.dti[0] = 10.f;
    block8_1.dti[1] = 10.f;
    block8_1.dti[2] = 20.f;
    block8_1.dti[3] = 20.f;

/* FIRST SPECIFY YOUR COMPUTERS CHANNEL NUMBERS .................... */
/* AGNR=OUTPUT (OUTPUT IS DISPLAYED OR STORED IN FILE OUTPUT.IRI)... */
/* IUCCIR=UNIT NUMBER FOR CCIR COEFFICIENTS ........................ */

    monito = 6;
    iuccir = 10;
    if (jf[12]) {
	konsol = 25;
	o__1.oerr = 1;
	o__1.ounit = konsol;
	o__1.ofnmlen = 9;
	o__1.ofnm = "/dev/null";
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	i__1 = f_open(&o__1);
	if (i__1 != 0) {
	    goto L8448;
	}
    } else {
	konsol = stderr;
    }

/* selection of density and ion composition options .................. */

    noden = ! jf[1];
    notem = ! jf[2];
    noion = ! jf[3];
    dy = ! jf[6];
    layver = ! jf[11];
    old79 = ! jf[7];
    gulb0 = ! jf[4];

/* f peak density .................................................... */

    fof2in = ! jf[8];
    if (fof2in) {
	afof2 = oarr[1];
	if (afof2 > 100.f) {
	    afof2 = sqrt(afof2 / 1.24e10f);
	}
    }
    ursif2 = ! jf[5];

/* f peak altitude .................................................. */

    hmf2in = ! jf[9];
    if (hmf2in) {
	ahmf2 = oarr[2];
    }

/* TE-NE MODEL OPTION .............................................. */

    teneop = ! jf[10];
    if (teneop) {
	for (jxnar = 1; jxnar <= 3; ++jxnar) {
	    xnar[jxnar - 1] = oarr[jxnar + 2];
	    tcon[jxnar - 1] = FALSE_;
/* L8154: */
	    if (xnar[jxnar - 1] > 0.f) {
		tcon[jxnar - 1] = TRUE_;
	    }
	}
    }
    if (icalls > 1) {
	goto L8201;
    }
    io___35.ciunit = konsol;
    s_wsle(&io___35);
    do_lio(&c__9, &c__1, "*** IRI parameters are being calculated ***", (
	    ftnlen)43);
    e_wsle();
    if (noden) {
	goto L2889;
    }
    if (layver) {
	io___36.ciunit = konsol;
	s_wsle(&io___36);
	do_lio(&c__9, &c__1, "Ne, E-F: The LAY-Version is ", (ftnlen)28);
	do_lio(&c__9, &c__1, "prelimenary. Erroneous profile features can oc"
		"cur.", (ftnlen)50);
	e_wsle();
    }
    if (gulb0) {
	io___37.ciunit = konsol;
	s_wsle(&io___37);
	do_lio(&c__9, &c__1, "Ne, B0: Bottomside thickness is ", (ftnlen)32);
	do_lio(&c__9, &c__1, "obtained with Gulyaeva-1987 model.", (ftnlen)34)
		;
	e_wsle();
    }
    if (old79) {
	io___38.ciunit = konsol;
	s_wsle(&io___38);
	do_lio(&c__9, &c__1, "Ne: Using IRI-79. Correction", (ftnlen)28);
	do_lio(&c__9, &c__1, " of equatorial topside is not included.", (
		ftnlen)39);
	e_wsle();
    }
    if (hmf2in) {
	io___39.ciunit = konsol;
	s_wsle(&io___39);
	do_lio(&c__9, &c__1, "Ne, hmF2: Input values are used.", (ftnlen)32);
	e_wsle();
    }
    if (fof2in) {
	io___40.ciunit = konsol;
	s_wsle(&io___40);
	do_lio(&c__9, &c__1, "Ne, foF2: Input values are used.", (ftnlen)32);
	e_wsle();
	goto L2889;
    }
    if (ursif2) {
	io___41.ciunit = konsol;
	s_wsle(&io___41);
	do_lio(&c__9, &c__1, "Ne, foF2: URSI model is used.", (ftnlen)29);
	e_wsle();
    } else {
	io___42.ciunit = konsol;
	s_wsle(&io___42);
	do_lio(&c__9, &c__1, "Ne, foF2: CCIR model is used.", (ftnlen)29);
	e_wsle();
    }
L2889:
    if (! noion && dy) {
	io___43.ciunit = konsol;
	s_wsle(&io___43);
	do_lio(&c__9, &c__1, "Ion Com.: Using Danilov-Yaichnikov-1985.", (
		ftnlen)40);
	e_wsle();
    }
    if (! notem && teneop) {
	io___44.ciunit = konsol;
	s_wsle(&io___44);
	do_lio(&c__9, &c__1, "Te: Temperature-density correlation is used", (
		ftnlen)43);
	e_wsle();
    }
L8201:

/* CALCULATION OF MEAN F10.7CM SOLAR RADIO FLUX (COV)................ */
/* CALCULATION OF RESTRICTED SOLAR ACTIVITIES (RG,COVG).............. */

    if (*rz12 >= 0.f) {
	r__ = *rz12;
	cov = r__ * (r__ * 8.9e-4f + .728f) + 63.75f;
    } else {
	cov = -(*rz12);
	r__ = (sqrt(cov + 85.12f) - 12.2f) * 33.52f;
    }
    rg = r__;
    covg = cov;
    if (r__ > 150.f) {
	rg = 150.f;
    }
    if (cov > 193.f) {
	covg = 193.f;
    }

/* CALCULATION OF GEOG. OR GEOM. COORDINATES IN DEG.................... */
/* CALCULATION OF MAGNETIC INCLINATION (DIP), DECLINATION (DEC)........ */
/*   DIP LATITUDE (MAGBR) AND MODIFIED DIP (MODIP). ALL IN DEGREE...... */

    if (*jmag > 0) {
	mlat = *alati;
	mlong = *along;
	if (mlong < 0.f) {
	    mlong += 360.f;
	}
    } else {
	lati = *alati;
	longi = *along;
	if (longi < 0.f) {
	    longi += 360.f;
	}
    }
    ggm_(jmag, &longi, &lati, &mlong, &mlat);
    abslat = dabs(lati);
    fieldg_(&lati, &longi, &c_b47, &xma, &yma, &zma, &bet, &dip, &dec, &modip)
	    ;
    magbr = atan(tan(dip * const_1.umr) * .5f) / const_1.umr;
    absmlt = dabs(mlat);
    absmdp = dabs(modip);
    absmbr = dabs(magbr);

/* CALCULATION OF SEASON (SUMMER=2, WINTER=4).......................... */
/* CALCULATION OF DAY OF YEAR AND SUN DECLINATION...................... */

    if (*mmdd < 0) {
	daynr = -(*mmdd);
	moda_(&c__1, &month, &iday, &daynr);
    } else {
	month = *mmdd / 100;
	iday = *mmdd - month * 100;
	moda_(&c__0, &month, &iday, &daynr);
    }
    season = (integer) ((daynr + 45.f) / 92.f);
    if (season < 1) {
	season = 4;
    }
    nseson = season;
    seaday = daynr;
    if (lati > 0.f) {
	goto L5592;
    }
    season += -2;
    if (season < 1) {
	season += 4;
    }
    seaday = daynr + 183;
    if (seaday > 366) {
	seaday += -366;
    }

/* CALCULATION OF SOLAR ZENITH ANGLE (XHI/DEG)......................... */
/* NOON VALUE (XHINON)................................................. */

L5592:
    if (*dhour > 24.1f) {
	ut = *dhour - 25.f;
	hour = ut + longi / 15.f;
	if (hour > 24.f) {
	    hour += -24.f;
	}
    } else {
	hour = *dhour;
	ut = hour - longi / 15.f;
	if (ut < 0.f) {
	    ut += 24.f;
	}
    }
    soco_(&daynr, &hour, &lati, &longi, &sundec, &xhi, &sax, &sux);
    soco_(&daynr, &c_b51, &lati, &longi, &sunde1, &xhinon, &saxnon, &suxnon);
    block5_1.night = FALSE_;
    if (dabs(sax) > 25.f) {
	if (sax < 0.f) {
	    block5_1.night = TRUE_;
	}
	goto L1334;
    }
    if (sax <= sux) {
	goto L1386;
    }
    if (hour > sux && hour < sax) {
	block5_1.night = TRUE_;
    }
    goto L1334;
L1386:
    if (hour > sux || hour < sax) {
	block5_1.night = TRUE_;
    }

/* CALCULATION OF ELECTRON DENSITY PARAMETERS................ */

L1334:
    hnea = 65.f;
    if (block5_1.night) {
	hnea = 80.f;
    }
    hnee = 2e3f;
    if (noden) {
	goto L4933;
    }
    dela = 4.32f;
    if (absmdp >= 18.f) {
	dela = exp(-(absmdp - 30.f) / 10.f) + 1.f;
    }
    dell = exp(-(abslat - 20.f) / 10.f) + 1;
/* !!!!!!! F-REGION PARAMETERS AND E-PEAK !!!!!!!!!!!!!!!!!!!!!!!!!! */
    foe = foeedi_(&cov, &xhi, &xhinon, &abslat);
    block4_1.nme = foe * 1.24e10f * foe;
    block4_1.hme = 105.f;
    if (fof2in && hmf2in) {
	goto L501;
    }
    if (ursif2 != ursifo) {
	goto L7797;
    }
    if (month == montho && rg == rgo) {
	goto L4292;
    }
    if (month == montho) {
	goto L4291;
    }

/* READ CCIR COEFFICIENT SET FOR CHOSEN MONTH.................... */

L7797:
    s_wsfi(&io___90);
    i__1 = month + 10;
    do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
    e_wsfi();
    dfp_(direct + 1, filename, path, (ftnlen)1, (ftnlen)1, (ftnlen)1);
    o__1.oerr = 1;
    o__1.ounit = iuccir;
    o__1.ofnmlen = 6;
    o__1.ofnm = "./PATH";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L8448;
    }
    io___92.ciunit = iuccir;
    s_rsfe(&io___92);
    do_fio(&c__1976, (char *)&f2[0], (ftnlen)sizeof(real));
    do_fio(&c__882, (char *)&fm3[0], (ftnlen)sizeof(real));
    e_rsfe();
    cl__1.cerr = 0;
    cl__1.cunit = iuccir;
    cl__1.csta = 0;
    f_clos(&cl__1);

/* READ URSI COEFFICIENT SET FOR CHOSEN MONTH.................... */

    if (ursif2) {
	s_wsfi(&io___95);
	i__1 = month + 10;
	do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	e_wsfi();
	dfp_(direct + 1, filename, path, (ftnlen)1, (ftnlen)1, (ftnlen)1);
	o__1.oerr = 1;
	o__1.ounit = iuccir;
	o__1.ofnmlen = 6;
	o__1.ofnm = "./PATH";
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	i__1 = f_open(&o__1);
	if (i__1 != 0) {
	    goto L8448;
	}
	io___96.ciunit = iuccir;
	s_rsfe(&io___96);
	do_fio(&c__1976, (char *)&f2[0], (ftnlen)sizeof(real));
	e_rsfe();
	cl__1.cerr = 0;
	cl__1.cunit = iuccir;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    ursifo = ursif2;
    montho = month;
    goto L4291;
L8448:
    io___97.ciunit = stderr;
    s_wsle(&io___97);
    do_lio(&c__9, &c__1, "./PATH IRI90: File not found", (ftnlen)28);
    e_wsle();
    s_stop("1", (ftnlen)1);
/* LINEAR INTERPOLATION IN SOLAR ACTIVITY */

L4291:
    rr2 = rg / 100.f;
    rr1 = 1.f - rr2;
    for (i__ = 1; i__ <= 76; ++i__) {
	for (j = 1; j <= 13; ++j) {
	    k = j + (i__ - 1) * 13;
/* L20: */
	    ff0[k - 1] = f2[j + (i__ + 76) * 13 - 1002] * rr1 + f2[j + (i__ + 
		    152) * 13 - 1002] * rr2;
	}
    }
    for (i__ = 1; i__ <= 49; ++i__) {
	for (j = 1; j <= 9; ++j) {
	    k = j + (i__ - 1) * 9;
/* L30: */
	    xm0[k - 1] = fm3[j + (i__ + 49) * 9 - 451] * rr1 + fm3[j + (i__ + 
		    98) * 9 - 451] * rr2;
	}
    }
    rgo = rg;
L4292:
    f2out_(&modip, &lati, &longi, ff0, xm0, &ut, &yfof2, &xm3000);
L501:
    if (fof2in) {
	fof2 = afof2;
    } else {
	fof2 = yfof2;
    }
    block1_1.nmf2 = fof2 * 1.24e10f * fof2;
    if (hmf2in) {
	block1_1.hmf2 = ahmf2;
    } else {
	r__1 = fof2 / foe;
	block1_1.hmf2 = hmf2ed_(&magbr, &rg, &r__1, &xm3000);
    }
    topsi = heiend > block1_1.hmf2;
    botto = heiend >= block4_1.hme && heibeg <= block1_1.hmf2;
    belowe = heibeg < block4_1.hme;

/* topside profile parameters ............................. */

    if (! topsi) {
	goto L1501;
    }
    cos2 = cos(mlat * const_1.umr);
    cos2 *= cos2;
    flu = (covg - 40.f) / 30.f;
    if (old79) {
	eta1 = cos2 * -.0070305f;
    } else {
	ex = exp(-mlat / 15.f);
	ex1 = ex + 1;
	epin = ex * 4.f / (ex1 * ex1);
	eta1 = epin * -.02f;
    }
    blo10_1.eta = eta1 + .058798f + flu * (cos2 * .0069724f - .014065f) + (
	    cos2 * .004281f + .0024287f - fof2 * 1.528e-4f) * fof2;
    blo10_1.zeta = .078922f - cos2 * .0046702f + flu * (cos2 * .0076545f - 
	    .019132f) + (cos2 * .006029f + .0032513f - fof2 * 2.0872e-4f) * 
	    fof2;
    blo10_1.beta = cos2 * 20.253f - 128.03f + flu * (-8.0755f - cos2 * 
	    .65896f) + (cos2 * .71458f + .44041f - fof2 * .042966f) * fof2;
    z__ = exp(94.45f / blo10_1.beta);
    z1 = z__ + 1;
    z2 = z__ / (blo10_1.beta * z1 * z1);
    blo10_1.delta = (blo10_1.eta / z1 - blo10_1.zeta / 2.f) / (blo10_1.eta * 
	    z2 + blo10_1.zeta / 400.f);

/* bottomside profile parameters ............................. */

L1501:
    block1_1.hmf1 = block1_1.hmf2;
    block3_1.hz = block1_1.hmf2;
    block4_1.hef = block4_1.hme;
    if (! botto) {
	goto L2727;
    }
    block2_1.b1 = 3.f;
/* !!!!!!! INTERPOLATION FOR B0 OUT OF ARRAY B0F !!!!!!!!!!!!!!!!!!!!! */
    if (gulb0) {
	rogul_(&seaday, &xhi, &seax, &grat);
	if (block5_1.night) {
	    grat = .91f - block1_1.hmf2 / 4e3f;
	}
	b0cnew = block1_1.hmf2 * (1.f - grat);
	block2_1.b0 = b0cnew / b0b1[0];
    } else {
	block2_1.b0 = b0pol_(&hour, &sax, &sux, &season, &rg, &dela);
    }
/* !!!!!!! F1-REGION PARAMETERS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    f1reg = FALSE_;
    block1_1.hmf1 = 0.f;
    pnmf1 = 0.f;
    block2_1.c1 = 0.f;
    if (block5_1.night || season == 4) {
	goto L150;
    }
    fof1 = fof1ed_(&absmbr, &r__, &xhi);
    if (fof1 < .001f) {
	goto L150;
    }
    f1reg = TRUE_;
    block2_1.c1 = .11f / dela + .09f;
    pnmf1 = fof1 * 1.24e10f * fof1;
L150:
    nmf1 = pnmf1;
/* !!!!!!! PARAMETER FOR E AND VALLEY-REGION !!!!!!!!!!!!!!!!!!!!! */
    xdel = xdels[season - 1] / dela;
    dndhbr = dnds[season - 1] / dela;
    r__1 = 10.5f / dela;
    hdeep = hpol_(&hour, &r__1, &c_b83, &sax, &sux, &c_b84, &c_b84);
    r__1 = 17.8f / dela;
    r__2 = 22.f / dela + 45.f;
    width = hpol_(&hour, &r__1, &r__2, &sax, &sux, &c_b84, &c_b84);
    depth = hpol_(&hour, &xdel, &c_b88, &sax, &sux, &c_b84, &c_b84);
    dlndh = hpol_(&hour, &dndhbr, &c_b91, &sax, &sux, &c_b84, &c_b84);
    if (depth < 1.f) {
	goto L600;
    }
    if (block5_1.night) {
	depth = -depth;
    }
    tal_(&hdeep, &depth, &width, &dlndh, &ext, block5_1.e);
    if (! ext) {
	goto L667;
    }
    io___134.ciunit = konsol;
    s_wsfe(&io___134);
    e_wsfe();
L600:
    width = 0.f;
L667:
    block4_1.hef = block4_1.hme + width;
    vner = (1.f - dabs(depth) / 100.f) * block4_1.nme;

/* Parameters below E  ............................. */

L2727:
    if (! belowe) {
	goto L2726;
    }
/* !!!!!!!D-REGION PARAMETER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    block6_1.nmd = xmded_(&xhi, &r__, &c_b99);
    block6_1.hmd = hpol_(&hour, &c_b88, &c_b101, &sax, &sux, &c_b84, &c_b84);
    r__1 = .03f / dela + .02f;
    f[0] = hpol_(&hour, &r__1, &c_b104, &sax, &sux, &c_b84, &c_b84);
    f[1] = hpol_(&hour, &c_b107, &c_b108, &sax, &sux, &c_b84, &c_b84);
    f[2] = hpol_(&hour, &c_b111, &c_b112, &sax, &sux, &c_b84, &c_b84);
    block7_1.fp1 = f[0];
    block7_1.fp2 = -block7_1.fp1 * block7_1.fp1 / 2.f;
    block7_1.fp30 = (-f[1] * block7_1.fp2 - block7_1.fp1 + 1.f / f[1]) / (f[1]
	     * f[1]);
    block7_1.fp3u = (-f[2] * block7_1.fp2 - block7_1.fp1 - 1.f / f[2]) / (f[2]
	     * f[2]);
    block6_1.hdx = block6_1.hmd + f[1];
    x = block6_1.hdx - block6_1.hmd;
    xdx = block6_1.nmd * exp(x * (block7_1.fp1 + x * (block7_1.fp2 + x * 
	    block7_1.fp30)));
    dxdx = xdx * (block7_1.fp1 + x * (block7_1.fp2 * 2.f + x * 3.f * 
	    block7_1.fp30));
    x = block4_1.hme - block6_1.hdx;
    block7_1.xkk = -dxdx * x / (xdx * log(xdx / block4_1.nme));
    d__1 = (doublereal) x;
    d__2 = (doublereal) (block7_1.xkk - 1.f);
    block7_1.d1 = dxdx / (xdx * block7_1.xkk * pow_dd(&d__1, &d__2));

/* SEARCH FOR HMF1 .................................................. */

L2726:
    if (! botto) {
	goto L4933;
    }
    if (layver) {
	goto L6153;
    }
L924:
    if (! f1reg) {
	goto L380;
    }
    xe2h = xe2_(&block4_1.hef);
    regfa1_(&block4_1.hef, &block1_1.hmf2, &xe2h, &block1_1.nmf2, &c_b118, &
	    nmf1, (E_fp)xe2_, &schalt, &block1_1.hmf1);
    if (! schalt) {
	goto L380;
    }
    io___142.ciunit = konsol;
    s_wsfe(&io___142);
    e_wsfe();
    iregfa = 1;

/* change B1 and try again .......................................... */

L9244:
    if (block2_1.b1 > 4.5f) {
	switch (iregfa) {
	    case 1:  goto L7398;
	    case 2:  goto L8922;
	}
    }
    block2_1.b1 += .5f;
    io___144.ciunit = konsol;
    s_wsfe(&io___144);
    r__1 = block2_1.b1 - .5f;
    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&block2_1.b1, (ftnlen)sizeof(real));
    e_wsfe();
    if (gulb0) {
	ib1 = (integer) (block2_1.b1 * 2.f - 5.f);
	block2_1.b0 = b0cnew / b0b1[ib1 - 1];
    }
    goto L924;

/* omit F1 feature .................................................... */

L7398:
    io___146.ciunit = konsol;
    s_wsfe(&io___146);
    e_wsfe();
    block1_1.hmf1 = 0.f;
    nmf1 = 0.f;
    block2_1.c1 = 0.f;
    block2_1.b1 = 3.f;
    f1reg = FALSE_;

/* SEARCH FOR HST [NE3(HST)=NME] .......................................... */

L380:
    rrrr = .5f;
    if (f1reg) {
	hf1 = block1_1.hmf1;
	xf1 = nmf1;
	goto L3972;
    }
    rathh = .5f;
L3973:
    hf1 = block4_1.hef + (block1_1.hmf2 - block4_1.hef) * rathh;
    xf1 = xe3_(&hf1);
    if (xf1 < block4_1.nme) {
	rathh += .1f;
	goto L3973;
    }
L3972:
    h__ = hf1;
    deh = 10.f;
    xxmin = xf1;
    hhmin = hf1;
L3895:
    h__ -= deh;
    if (h__ < block4_1.hef) {
	h__ += deh * 2;
	deh /= 10.f;
	if (deh < 1.f) {
	    goto L3885;
	}
    }
    xe3h = xe3_(&h__);
    if (xe3h < xxmin) {
	xxmin = xe3h;
	hhmin = h__;
    }
    if (xe3h > block4_1.nme) {
	goto L3895;
    }
    regfa1_(&h__, &hf1, &xe3h, &xf1, &c_b118, &block4_1.nme, (E_fp)xe3_, &
	    schalt, &block3_1.hst);
    block3_1.str = block3_1.hst;
    if (! schalt) {
	goto L360;
    }
L3885:
    io___156.ciunit = konsol;
    s_wsfe(&io___156);
    e_wsfe();
    iregfa = 2;
    if (xxmin / block4_1.nme < 1.3f) {
	goto L9244;
    }

/* assume linear interpolation between HZ and HEF .................. */

L8922:
    block3_1.hz = hhmin + (hf1 - hhmin) * rrrr;
    xnehz = xe3_(&block3_1.hz);
    if (xnehz - block4_1.nme < .001f) {
	rrrr += .1f;
	goto L8922;
    }
    io___158.ciunit = konsol;
    s_wsfe(&io___158);
    do_fio(&c__1, (char *)&block3_1.hz, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&block4_1.hef, (ftnlen)sizeof(real));
    e_wsfe();
    block3_1.t = (xnehz - block4_1.nme) / (block3_1.hz - block4_1.hef);
    block3_1.hst = -333.f;
    goto L4933;

/* calculate HZ, D and T ............................................ */

L360:
    block3_1.hz = (block3_1.hst + hf1) / 2.f;
    d__ = block3_1.hz - block3_1.hst;
    block3_1.t = d__ * d__ / (block3_1.hz - block4_1.hef - d__);
    goto L4933;

/* LAY-functions for middle ionosphere */

L6153:
    hmf1m = xhi * .6428f + 165.f;
    hhalf = grat * block1_1.hmf2;
    hv1r = block4_1.hme + width;
    hv2r = block4_1.hme + hdeep;
    hhmf2 = block1_1.hmf2;
    inilay_(&block5_1.night, &block1_1.nmf2, &nmf1, &block4_1.nme, &vner, &
	    hhmf2, &hmf1m, &block4_1.hme, &hv1r, &hv2r, &hhalf, hxl, scl, amp,
	     &iiqu);
    if (iiqu == 1) {
	io___168.ciunit = konsol;
	s_wsfe(&io___168);
	e_wsfe();
    }
    if (iiqu == 2) {
	io___169.ciunit = konsol;
	s_wsfe(&io___169);
	e_wsfe();
    }
/* ---------- CALCULATION OF NEUTRAL TEMPERATURE PARAMETER------- */
L4933:
    hta = 120.f;
    hte = 3e3f;
    if (notem) {
	goto L240;
    }
    sec = ut * 3600.f;
    cira86_(&daynr, &sec, &lati, &longi, &hour, &cov, &blotn_1.texos, &tn120, 
	    &blotn_1.sigma);
    if (hour != 0.f) {
	secni = (24.f - longi / 15.f) * 3600.f;
	cira86_(&daynr, &secni, &lati, &longi, &c_b147, &cov, &texni, &tn1ni, 
		&signi);
    } else {
	texni = blotn_1.texos;
	tn1ni = tn120;
	signi = blotn_1.sigma;
    }
    blotn_1.tlbdh = blotn_1.texos - tn120;
    tlbdn = texni - tn1ni;

/* --------- CALCULATION OF ELECTRON TEMPERATURE PARAMETER-------- */

/* L881: */
/* !!!!!!!!!! TE(120KM)=TN(120KM) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    ate[0] = tn120;
/* !!!!!!!!!! TE-MAXIMUM (JICAMARCA,ARECIBO) !!!!!!!!!!!!!!!!!!!! */
/* Computing 2nd power */
    r__1 = mlat / 22.41f;
    hmaxd = exp(-(r__1 * r__1)) * 60.f + 210.f;
    hmaxn = 150.f;
    blote_1.ahh[1] = hpol_(&hour, &hmaxd, &hmaxn, &sax, &sux, &c_b84, &c_b84);
/* Computing 2nd power */
    r__1 = mlat / 33.f;
    tmaxd = exp(-(r__1 * r__1)) * 800.f + 1500.f;
    tmaxn = tn_(&hmaxn, &texni, &tlbdn, &signi) + 20;
    ate[1] = hpol_(&hour, &tmaxd, &tmaxn, &sax, &sux, &c_b84, &c_b84);
/* !!!!!!!!!! TE(300,400KM)=TE-AE-C !!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!! TE(1400,3000KM)=TE-ISIS !!!!!!!!!!!!!!!!!!!!!!!!!!! */
    diplat = magbr;
    teba_(&diplat, &hour, &nseson, tea);
    ate[2] = tea[0];
    ate[3] = tea[1];
    ate[5] = tea[2];
    ate[6] = tea[3];
/* !!!!!!!!!! TE(600KM)=TE-AEROS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    ett = exp(-mlat / 11.35f);
    d__1 = (doublereal) (ett + 1);
    tet = 2900.f - ett * 5600.f / pow_dd(&d__1, &c_b153);
    ten = 1161.f / (exp(-(absmlt - 45.f) / 5.f) + 1.f) + 839.f;
    ate[4] = hpol_(&hour, &tet, &ten, &sax, &sux, &c_b154, &c_b154);
/* !!!!!!!!!! OPTION TO USE TE-NE-RELATION !!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!! AT 300, 400 OR 600 KM  !!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    if (teneop) {
	for (i__ = 1; i__ <= 3; ++i__) {
/* L3395: */
	    if (tcon[i__ - 1]) {
		r__1 = -cov;
		ate[i__ + 1] = tede_(&hoa[i__ - 1], &xnar[i__ - 1], &r__1);
	    }
	}
    }
/* !!!!!!!!!! TE'S ARE CORRECTED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!! ALSO TE > TN ENFORCED !!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    tnahh2 = tn_(&blote_1.ahh[1], &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    if (ate[1] < tnahh2) {
	ate[1] = tnahh2;
    }
    stte1 = (ate[1] - ate[0]) / (blote_1.ahh[1] - blote_1.ahh[0]);
    for (i__ = 2; i__ <= 6; ++i__) {
	tnahhi = tn_(&blote_1.ahh[i__], &blotn_1.texos, &blotn_1.tlbdh, &
		blotn_1.sigma);
	if (ate[i__] < tnahhi) {
	    ate[i__] = tnahhi;
	}
	stte2 = (ate[i__] - ate[i__ - 1]) / (blote_1.ahh[i__] - blote_1.ahh[
		i__ - 1]);
	ate[i__ - 1] -= (stte2 - stte1) * blote_1.dte[i__ - 2] * alog2;
/* L1901: */
	stte1 = stte2;
    }
/* !!!!!!!!!! GRADIENTS ARE CALCULATED WITH !!!!!!!!!!!!!!!!!!!! */
/* !!!!!!!!!! CORRECTED REGION BOUNDARIES !!!!!!!!!!!!!!!!!!!!!! */
    for (i__ = 1; i__ <= 6; ++i__) {
/* L1902: */
	blote_1.stte[i__ - 1] = (ate[i__] - ate[i__ - 1]) / (blote_1.ahh[i__] 
		- blote_1.ahh[i__ - 1]);
    }
    blote_1.ate1 = ate[0];
/* L887: */

/* ------------ CALCULATION OF ION TEMPERATURE PARAMETERS-------- */

/* !!!!!!!!!! TI(430KM,DAY)=TI-AEROS !!!!!!!!!!!!!!!!!!!!!!!!!!! */
    blotn_1.xsm1 = 430.f;
    block8_1.xsm[0] = blotn_1.xsm1;
    z1 = exp(mlat * -.09f);
    z2 = z1 + 1.f;
    tid1 = 1240.f - z1 * 1400.f / (z2 * z2);
    block8_1.mm[1] = hpol_(&hour, &c_b160, &c_b147, &sax, &sux, &c_b84, &
	    c_b84);
/* !!!!!!!!!!  TI < TE   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    ted1 = tea[5] + 30.f;
    if (tid1 > ted1) {
	tid1 = ted1;
    }
/* !!!!!!!!!! TI(430KM,NIGHT)=TI-AEROS !!!!!!!!!!!!!!!!!!!!!!!!! */
    z1 = absmlt;
    z2 = z1 * (z1 * .024f + .47f) * const_1.umr;
    z3 = cos(z2);
    tin1 = 1200.f - r_sign(&c_b84, &z3) * 300.f * sqrt((dabs(z3)));
/* !!!!!!!!!! TN < TI < TE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    ten1 = tea[4];
    tnn1 = tn_(&blotn_1.xsm1, &texni, &tlbdn, &signi);
    if (ten1 < tnn1) {
	ten1 = tnn1;
    }
    if (tin1 > ten1) {
	tin1 = ten1;
    }
    if (tin1 < tnn1) {
	tin1 = tnn1;
    }
/* !!!!!!!!!! TI(430KM,LT) FROM STEP FUNCTION !!!!!!!!!!!!!!!!!! */
    ti1 = tin1;
    if (tid1 > tin1) {
	ti1 = hpol_(&hour, &tid1, &tin1, &sax, &sux, &c_b84, &c_b84);
    }
/* !!!!!!!!!! TANGENT ON TN DETERMINES HS !!!!!!!!!!!!!!!!!!!!!! */
    ti13 = teder_(&c_b167);
    ti50 = teder_(&c_b168);
    regfa1_(&c_b167, &c_b168, &ti13, &ti50, &c_b171, &ti1, (E_fp)teder_, &
	    schalt, &block8_1.hs);
    if (schalt) {
	block8_1.hs = 200.f;
    }
    block8_1.tnhs = tn_(&block8_1.hs, &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    block8_1.mm[0] = dtndh_(&block8_1.hs, &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    if (schalt) {
	block8_1.mm[0] = (ti1 - block8_1.tnhs) / (blotn_1.xsm1 - block8_1.hs);
    }
    block8_1.mxsm = 2;
/* !!!!!!!!!! XTETI ALTITTUDE WHERE TE=TI !!!!!!!!!!!!!!!!!!!!!! */
/* L2391: */
    xtts = 500.f;
    x = 500.f;
L2390:
    x += xtts;
    if (x >= blote_1.ahh[6]) {
	goto L240;
    }
    tex = elte_(&x);
    tix = ti_(&x);
    if (tix < tex) {
	goto L2390;
    }
    x -= xtts;
    xtts /= 10.f;
    if (xtts > .1f) {
	goto L2390;
    }
    xteti = x + xtts * 5.f;
/* !!!!!!!!!! TI=TE ABOVE XTETI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    block8_1.mxsm = 3;
    block8_1.mm[2] = blote_1.stte[5];
    block8_1.xsm[1] = xteti;
    if (xteti > blote_1.ahh[5]) {
	goto L240;
    }
    block8_1.mxsm = 4;
    block8_1.mm[2] = blote_1.stte[4];
    block8_1.mm[3] = blote_1.stte[5];
    block8_1.xsm[2] = blote_1.ahh[5];
    if (xteti > blote_1.ahh[4]) {
	goto L240;
    }
    block8_1.mxsm = 5;
    block8_1.dti[0] = 5.f;
    block8_1.dti[1] = 5.f;
    block8_1.mm[2] = blote_1.stte[3];
    block8_1.mm[3] = blote_1.stte[4];
    block8_1.mm[4] = blote_1.stte[5];
    block8_1.xsm[2] = blote_1.ahh[4];
    block8_1.xsm[3] = blote_1.ahh[5];

/* CALCULATION OF ION DENSITY PARAMETER.................. */

L240:
    if (noion) {
	goto L141;
    }
    hnia = 100.f;
    hnie = 2e3f;
    if (dy) {
	goto L141;
    }

/* INPUT OF THE ION DENSITY PARAMETER ARRAYS PF1O,PF2O AND PF3O...... */

    rif[0] = 2.f;
    if (abslat < 30.f) {
	rif[0] = 1.f;
    }
    rif[1] = 2.f;
    if (cov < 100.f) {
	rif[1] = 1.f;
    }
    rif[2] = (real) season;
    if (season == 1) {
	rif[2] = 3.f;
    }
    rif[3] = 1.f;
    if (block5_1.night) {
	rif[3] = 2.f;
    }
    koefp1_(pg1o);
    koefp2_(pg2o);
    koefp3_(pg3o);
    sufe_(pg1o, rif, &c__12, pf1o);
    sufe_(pg2o, rif, &c__4, pf2o);
    sufe_(pg3o, rif, &c__12, pf3o);

/* calculate O+ profile parameters */

    if (dabs(xhi) <= 90.f) {
	zzz1 = cos(xhi * const_1.umr);
    } else {
	zzz1 = 0.f;
    }
    msumo = 4;
    rdomax = 100.f;
    mo[0] = epstep_(pf1o, &pf1o[1], &pf1o[2], &pf1o[3], &zzz1);
    mo[1] = epstep_(&pf1o[4], &pf1o[5], &pf1o[6], &pf1o[7], &zzz1);
    mo[2] = 0.f;
    ho[0] = epstep_(&pf1o[8], &pf1o[9], &pf1o[10], &pf1o[11], &zzz1);
    ho[1] = 290.f;
    if (rif[1] == 2.f && rif[2] == 2.f) {
	ho[1] = 237.f;
    }
    ho[3] = pf2o[0];
    ho05 = pf2o[3];
    mo[3] = pf2o[1];
    mo[4] = pf2o[2];

/* adjust gradient MO(4) of O+ profile segment above F peak */

L7100:
    ho[2] = (alg100 - mo[4] * (ho[3] - ho05)) / mo[3] + ho[3];
    if (ho[2] <= ho[1] + 20.f) {
	mo[3] += -.001f;
	goto L7100;
    }
    hfixo = (ho[1] + ho[2]) / 2.f;

/* find height H0O of maximum O+ relative density */

    delx = 5.f;
    x = ho[1];
    ymaxx = 0.f;
L7102:
    x += delx;
    y = rpid_(&x, &hfixo, &rdomax, &msumo, mo, ddo, ho);
    if (y <= ymaxx) {
	if (delx <= .1f) {
	    goto L7104;
	}
	x -= delx;
	delx /= 5.f;
    } else {
	ymaxx = y;
    }
    goto L7102;
L7104:
    h0o = x - delx / 2.f;
L7101:
    if (y < 100.f) {
	goto L7103;
    }
    rdomax += -.01f;
    y = rpid_(&h0o, &hfixo, &rdomax, &msumo, mo, ddo, ho);
    goto L7101;
L7103:
    yo2h0o = 100.f - y;
    yoh0o = y;

/* calculate parameters for O2+ profile */

    hfixo2 = pf3o[0];
    rdo2mx = pf3o[1];
    for (l = 1; l <= 2; ++l) {
	i__ = l << 1;
	ho2[l - 1] = pf3o[i__] + pf3o[i__ + 1] * zzz1;
/* L7105: */
	mo2[l] = pf3o[i__ + 6] + pf3o[i__ + 7] * zzz1;
    }
    mo2[0] = pf3o[6] + pf3o[7] * zzz1;
    if (hfixo2 > ho2[0]) {
	ymo2z = mo2[1];
    } else {
	ymo2z = mo2[0];
    }
    aldo21 = log(rdo2mx) + ymo2z * (ho2[0] - hfixo2);
    hfixo2 = (ho2[1] + ho2[0]) / 2.f;
    rdo2mx = exp(aldo21 + mo2[1] * (hfixo2 - ho2[0]));

/* make sure that rd(O2+) is less or equal 100-rd(O+) at O+ maximum */

L7106:
    y = rpid_(&h0o, &hfixo2, &rdo2mx, &c__2, mo2, do2, ho2);
    if (y > yo2h0o) {
	mo2[2] += -.02f;
	goto L7106;
    }

/* use ratio of NO+ to O2+ density at O+ maximum to calculate */
/* NO+ density above the O+ maximum (H0O) */

    if (y < 1.f) {
	nobo2 = 0.f;
    } else {
	nobo2 = (yo2h0o - y) / y;
    }

/* CALCULATION FOR THE REQUIRED HEIGHT RANGE....................... */

L141:
    if (! f1reg) {
	block1_1.hmf1 = block3_1.hz;
    }
    for (ki = 1; ki <= 11; ++ki) {
	i__1 = *nz;
	for (kk = 1; kk <= i__1; ++kk) {
/* L7397: */
	    outf[ki + kk * 11] = -1.f;
	}
    }
    i__1 = *nz;
    for (kk = 1; kk <= i__1; ++kk) {
	height = zkm[kk];
/* L300: */
	if (noden) {
	    goto L330;
	}
	if (height > hnee || height < hnea) {
	    goto L330;
	}
	if (layver) {
	    elede = -9.f;
	    if (iiqu < 2) {
		elede = xen_(&height, &block1_1.hmf2, &block1_1.nmf2, &
			block4_1.hme, &c__4, hxl, scl, amp);
	    }
	} else {
	    elede = xe_(&height);
	}
	outf[kk * 11 + 1] = elede;
L330:
	if (notem) {
	    goto L7108;
	}
	if (height > hte || height < hta) {
	    goto L7108;
	}
	tnh = tn_(&height, &blotn_1.texos, &blotn_1.tlbdh, &blotn_1.sigma);
	tih = tnh;
	if (height >= block8_1.hs) {
	    tih = ti_(&height);
	}
	teh = elte_(&height);
	if (tih < tnh) {
	    tih = tnh;
	}
	if (teh < tih) {
	    teh = tih;
	}
	outf[kk * 11 + 2] = tnh;
	outf[kk * 11 + 3] = tih;
	outf[kk * 11 + 4] = teh;
L7108:
	if (noion) {
	    goto L7118;
	}
	if (height > hnie || height < hnia) {
	    goto L7118;
	}
	if (dy) {
	    zmonth = month + iday / 30.f;
	    r__1 = xhi * const_1.umr;
	    r__2 = lati * const_1.umr;
	    ioncom_(&height, &r__1, &r__2, &cov, &zmonth, dion);
	    rox = dion[0];
	    rhx = dion[1];
	    rnx = dion[2];
	    rhex = dion[3];
	    rnox = dion[4];
	    ro2x = dion[5];
	    rclust = dion[6];
	} else {
	    rox = rpid_(&height, &hfixo, &rdomax, &msumo, mo, ddo, ho);
	    ro2x = rpid_(&height, &hfixo2, &rdo2mx, &c__2, mo2, do2, ho2);
	    rdhhe_(&height, &h0o, &rox, &ro2x, &nobo2, &c_b193, &rhx, &rhex);
	    rnox = rdno_(&height, &h0o, &ro2x, &rox, &nobo2);
	    rnx = -1.f;
	    rclust = -1.f;
	}
	outf[kk * 11 + 5] = rox;
	outf[kk * 11 + 6] = rhx;
	outf[kk * 11 + 7] = rhex;
	outf[kk * 11 + 8] = ro2x;
	outf[kk * 11 + 9] = rnox;
	outf[kk * 11 + 10] = rnx;
	outf[kk * 11 + 11] = rclust;
L7118:
	;
    }

/* ADDITIONAL PARAMETER FIELD OARR */

    if (noden) {
	goto L6192;
    }
    oarr[1] = block1_1.nmf2;
    oarr[2] = block1_1.hmf2;
    oarr[3] = nmf1;
    oarr[4] = block1_1.hmf1;
    oarr[5] = block4_1.nme;
    oarr[6] = block4_1.hme;
    oarr[7] = block6_1.nmd;
    oarr[8] = block6_1.hmd;
    oarr[9] = hhalf;
    oarr[10] = block2_1.b0;
    oarr[11] = vner;
    oarr[12] = block4_1.hef;
L6192:
    if (notem) {
	goto L6092;
    }
    oarr[13] = ate[1];
    oarr[14] = blote_1.ahh[1];
    oarr[15] = ate[2];
    oarr[16] = ate[3];
    oarr[17] = ate[4];
    oarr[18] = ate[5];
    oarr[19] = ate[6];
    oarr[20] = ate[0];
    oarr[21] = ti1;
    oarr[22] = xteti;
L6092:
    oarr[23] = xhi;
    oarr[24] = sundec;
    oarr[25] = dip;
    oarr[26] = magbr;
    oarr[27] = modip;
/* L3330: */
    cl__1.cerr = 0;
    cl__1.cunit = konsol;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* iri90_ */



/* Subroutine DFP, Stan Solomon, 3/92, splices filename to directory */

/* Subroutine */ int dfp_(char *direct, char *filename, char *path, ftnlen 
	direct_len, ftnlen filename_len, ftnlen path_len)
{
    /* Initialized data */

    static char blanks[50] = "                                              "
	    "    ";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer i_len(char *, ftnlen);

    /* Local variables */
    static integer i__, lb, le, nd, nch;

    s_copy(path, blanks, path_len, (ftnlen)50);
    nch = i_len(direct, direct_len);
    i__1 = nch;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (*(unsigned char *)&direct[i__ - 1] != ' ') {
	    goto L20;
	}
/* L10: */
    }
L20:
    lb = i__;
    for (i__ = nch; i__ >= 1; --i__) {
	if (*(unsigned char *)&direct[i__ - 1] != ' ') {
	    goto L40;
	}
/* L30: */
    }
L40:
    le = i__;
    if (lb >= nch || le <= 0) {
	s_copy(path, filename, (ftnlen)10, (ftnlen)10);
    } else {
	nd = le - lb + 1;
	s_copy(path, direct + (lb - 1), nd, le - (lb - 1));
	i__1 = nd;
	s_copy(path + i__1, filename, nd + 10 - i__1, (ftnlen)10);
    }
    return 0;
} /* dfp_ */





/* IRIF12.FOR ------------------------------------- OCTOBER 1991 */
/* ************************************************************** */
/* changes from IRIFU9 to IRIF10: */
/*       SOCO for solar zenith angle */
/* 	ACOS and ASIN argument forced to be within -1 / +1 */
/* 	EPSTEIN functions corrected for large arguments */
/* ************************************************************** */
/* changes from IRIF10 to IRIF11: */
/* 	LAY subroutines introduced */
/*       TEBA corrected for 1400 km */
/* ************************************************************** */
/* changes from IRIF11 to IRIF12: */
/*       Neutral temperature subroutines now in CIRA86.FOR */
/*       TEDER changed */
/*       All names with 6 or more characters replaced */
/* 	10/29/91 XEN: 10^ in loop, instead of at the end */

/* ************************************************************** */
/* ********** INTERNATIONAL REFERENCE IONOSPHERE **************** */
/* ************************************************************** */
/* ****************  FUNCTIONS,SUBROUTINES  ********************* */
/* ************************************************************** */
/* ** NE: 	XE1,DXE1N,XE2,XE3,XE4,XE5,XE6,XE */
/* ** TE/TI: 	TEBA,SPHARM,ELTE,TEDE,TI,TEDER */
/* ** NI:		RPID,RDHHE,RDNO,KOEFP1,KOEFP2,KOEFP3,SUFE */
/* ** PEAKS:	F2OUT,HMF2ED,FOF1ED,FOEEDI,XMDED,GAMMA1 */
/* ** MAG. FIELD: GGM,FIELDG */
/* ** FUNCTIONS: 	REGFA1,TAL */
/* ** TIME:	SOCO,HPOL,MODA */
/* ** INTERPOL.:	B0POL */
/* ** EPSTEIN:	RLAY,D1LAY,D2LAY,EPTR,EPST,EPSTEP,EPLA */
/* ** LAY:	XE2TO5,XEN,ROGUL,VALGUL,LNGLSN,LSKNM,INILAY */
/* ** NI-new:	IONCOM, RPDA */
/* ************************************************************** */

/* ************************************************************** */
/* ***  -------------------ADDRESSES------------------------  *** */
/* ***  I  PROF. K. RAWER             DR. D. BILITZA       I  *** */
/* ***  I  HERRENSTR. 43              GSFC CODE 933        I  *** */
/* ***  I  7801 MARCH 1               GREENBELT MD 20771   I  *** */
/* ***  I  F.R.G.                     USA                  I  *** */
/* ***  ----------------------------------------------------  *** */
/* ************************************************************** */
/* ************************************************************** */

/* ************************************************************* */
/* *************** ELECTRON DENSITY **************************** */
/* ************************************************************* */


doublereal xe1_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double r_sign(real *, real *), exp(doublereal);

    /* Local variables */
    static real x, y, x0, xmx0, dxdh;
    extern doublereal eptr_(real *, real *, real *);
    static real eptr1, eptr2;

/* ---------------------------------------------------------------- */
/* REPRESENTING ELECTRON DENSITY(M-3) IN THE TOPSIDE IONOSPHERE */
/* (H=HMF2....1000 KM) BY HARMONIZED BENT-MODEL ADMITTING */
/* VARIABILITY OFGLOBAL PARAMETER ETA,ZETA,BETA,DELTA WITH */
/* GEOM. LATITUDE, SMOOTHED SOLAR FLUX AND CRITICAL FREQUENCY */
/* (SEE MAIN PROGRAM). */
/* [REF.:K.RAWER,S.RAMAKRISHNAN,1978] */
/* ---------------------------------------------------------------- */
    dxdh = (1e3f - block1_2.hmf2) / 700.f;
    x0 = 300.f - blo10_1.delta;
    xmx0 = (*h__ - block1_2.hmf2) / dxdh;
    x = xmx0 + x0;
    eptr1 = eptr_(&x, &blo10_1.beta, &c_b205) - eptr_(&x0, &blo10_1.beta, &
	    c_b205);
    eptr2 = eptr_(&x, &c_b207, &c_b47) - eptr_(&x0, &c_b207, &c_b47);
    y = blo10_1.beta * blo10_1.eta * eptr1 + blo10_1.zeta * (eptr2 * 100.f - 
	    xmx0);
    y *= dxdh;
    if (dabs(y) > argexp_1.argmax) {
	y = r_sign(&argexp_1.argmax, &y);
    }
    ret_val = block1_2.xnmf2 * exp(-y);
    return ret_val;
} /* xe1_ */



doublereal dxe1n_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real x, x0;
    extern doublereal epst_(real *, real *, real *);
    static real epst1, epst2;

/* LOGARITHMIC DERIVATIVE OF FUNCTION XE1 (KM-1). */
    x0 = 300.f - blo10_1.delta;
    x = (*h__ - block1_2.hmf2) / (1e3f - block1_2.hmf2) * 700.f + x0;
    epst2 = epst_(&x, &c_b207, &c_b47);
    epst1 = epst_(&x, &blo10_1.beta, &c_b205);
    ret_val = -blo10_1.eta * epst1 + blo10_1.zeta * (1.f - epst2);
    return ret_val;
} /* dxe1n_ */



doublereal xe2_(real *h__)
{
    /* System generated locals */
    real ret_val;
    doublereal d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), exp(doublereal), cosh(
	    doublereal);

    /* Local variables */
    static real x, z__;

/* ELECTRON DENSITY FOR THE BOTTOMSIDE F-REGION (HMF1...HMF2). */
    x = (block1_2.hmf2 - *h__) / block2_1.b0;
    d__1 = (doublereal) x;
    d__2 = (doublereal) block2_1.b1;
    z__ = pow_dd(&d__1, &d__2);
    if (z__ > argexp_1.argmax) {
	z__ = argexp_1.argmax;
    }
    ret_val = block1_2.xnmf2 * exp(-z__) / cosh(x);
    return ret_val;
} /* xe2_ */



doublereal xe3_(real *h__)
{
    /* System generated locals */
    real ret_val, r__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    extern doublereal xe2_(real *);

/* ELECTRON DENSITY FOR THE F1-LAYER (HZ.....HMF1). */
    ret_val = xe2_(h__) + block1_2.xnmf2 * block2_1.c1 * sqrt((r__1 = 
	    block1_2.hmf1 - *h__, dabs(r__1)) / block2_1.b0);
    return ret_val;
} /* xe3_ */



doublereal xe4_(real *h__)
{
    /* System generated locals */
    real ret_val, r__1;

    /* Builtin functions */
    double r_sign(real *, real *), sqrt(doublereal);

    /* Local variables */
    extern doublereal xe3_(real *);

/* ELECTRON DENSITY FOR THE INDERMEDIUM REGION (HEF..HZ). */
    if (block3_1.hst < 0.f) {
	goto L100;
    }
    r__1 = block3_1.hz + block3_1.t / 2.f - r_sign(&c_b84, &block3_1.t) * 
	    sqrt(block3_1.t * (block3_1.hz - *h__ + block3_1.t / 4.f));
    ret_val = xe3_(&r__1);
    return ret_val;
L100:
    ret_val = block4_2.xnme + block3_1.t * (*h__ - block4_2.hef);
    return ret_val;
} /* xe4_ */



doublereal xe5_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real t1, t3;

/* ELECTRON DENSITY FOR THE E AND VALLEY REGION (HME..HEF). */
    t3 = *h__ - block4_2.hme;
    t1 = t3 * t3 * (block5_1.e[0] + t3 * (block5_1.e[1] + t3 * (block5_1.e[2] 
	    + t3 * block5_1.e[3])));
    if (block5_1.night) {
	goto L100;
    }
    ret_val = block4_2.xnme * (t1 + 1);
    return ret_val;
L100:
    ret_val = block4_2.xnme * exp(t1);
    return ret_val;
} /* xe5_ */



doublereal xe6_(real *h__)
{
    /* System generated locals */
    real ret_val;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static real z__, fp3;

/* ELECTRON DENSITY FOR THE D REGION (HA...HME). */
    if (*h__ > block6_2.hdx) {
	goto L100;
    }
    z__ = *h__ - block6_2.hmd;
    fp3 = block7_1.fp3u;
    if (z__ > 0.f) {
	fp3 = block7_1.fp30;
    }
    ret_val = block6_2.xnmd * exp(z__ * (block7_1.fp1 + z__ * (block7_1.fp2 + 
	    z__ * fp3)));
    return ret_val;
L100:
    z__ = block4_2.hme - *h__;
    d__1 = (doublereal) z__;
    d__2 = (doublereal) block7_1.xkk;
    ret_val = block4_2.xnme * exp(-block7_1.d1 * pow_dd(&d__1, &d__2));
    return ret_val;
} /* xe6_ */



doublereal xe_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal xe1_(real *), xe2_(real *), xe3_(real *), xe4_(real *), 
	    xe5_(real *), xe6_(real *);

/* ELECTRON DENSITY BEETWEEN HA(KM) AND 1000 KM */
/* SUMMARIZING PROCEDURES  NE1....6; */
    if (*h__ < block1_2.hmf2) {
	goto L100;
    }
    ret_val = xe1_(h__);
    return ret_val;
L100:
    if (*h__ < block1_2.hmf1) {
	goto L300;
    }
    ret_val = xe2_(h__);
    return ret_val;
L300:
    if (*h__ < block3_1.hz) {
	goto L400;
    }
    ret_val = xe3_(h__);
    return ret_val;
L400:
    if (*h__ < block4_2.hef) {
	goto L500;
    }
    ret_val = xe4_(h__);
    return ret_val;
L500:
    if (*h__ < block4_2.hme) {
	goto L600;
    }
    ret_val = xe5_(h__);
    return ret_val;
L600:
    ret_val = xe6_(h__);
    return ret_val;
} /* xe_ */


/* ********************************************************** */
/* ***************** ELECTRON TEMPERATURE ******************** */
/* ********************************************************** */

/* Subroutine */ int teba_(real *dipl, real *slt, integer *ns, real *te)
{
    /* Initialized data */

    static real c__[648]	/* was [4][2][81] */ = { 3.1f,3.136f,3.372f,
	    3.574f,3.13654f,3.144f,3.367f,3.574f,-.003215f,.006498f,.01006f,
	    0.f,.006796f,.008571f,.01038f,-.005639f,.244f,.2289f,.1436f,
	    .07537f,.181413f,.2539f,.1407f,.07094f,-4.613e-4f,.01859f,
	    .002023f,0.f,.08564f,.06937f,.03622f,-.03347f,-.01711f,-.03328f,
	    -.05166f,-.08459f,-.032856f,-.01667f,-.03144f,-.0861f,.02605f,
	    -.004889f,.009606f,0.f,-.003508f,.02249f,.0112f,-.02877f,-.09546f,
	    -.03054f,-.05596f,-.0294f,-.01438f,-.04162f,-.05674f,-.03154f,
	    .01794f,-.01773f,4.914e-4f,0.f,-.02454f,.01201f,.03219f,-.002847f,
	    .0127f,-.01728f,-.003124f,.04547f,.002745f,.02435f,.001288f,
	    .01235f,.02791f,.06555f,-.04713f,-.05321f,.05284f,.05232f,
	    -.05799f,-.05966f,.01536f,.01775f,-.007371f,0.f,.01136f,.02521f,
	    -.004609f,-.003236f,-.006629f,-.02488f,-.004823f,.004328f,
	    -.01956f,-.0199f,.003252f,3.795e-4f,-.003616f,-.009498f,-.002213f,
	    0.f,-.005805f,-.007671f,-2.859e-4f,-8.634e-4f,.01229f,.01493f,
	    .006569f,.006022f,.002801f,.01264f,.01226f,.003377f,4.147e-4f,
	    .00281f,-1.962e-4f,0.f,-.001211f,-.001551f,-.004539f,-1.071e-4f,
	    .001447f,.002406f,3.309e-4f,-9.168e-4f,.004127f,-.001928f,.00131f,
	    -.002151f,-4.453e-4f,.005436f,-3.908e-4f,0.f,.002909f,.003652f,
	    -5.603e-4f,-4.057e-4f,-.1853f,-.2115f,-.2836f,-.1768f,-.25751f,
	    -.2019f,-.311f,-.1783f,-.01245f,.007007f,.007829f,0.f,-.0037915f,
	    .005697f,-.001268f,.0126f,-.03675f,-.05129f,.01175f,.0294f,
	    -.0136f,-.03159f,.01539f,.02835f,.004965f,-.007327f,9.919e-4f,0.f,
	    -.013225f,-.01451f,.003146f,-.00242f,.00546f,.02402f,.006589f,
	    5.902e-4f,.01202f,.02868f,.007787f,.003002f,.008117f,.004772f,
	    .002045f,0.f,.01256f,.01377f,-.00143f,-.004684f,-.01002f,
	    -.007374f,-.007346f,-.009047f,-.012165f,-.004383f,-.00482f,
	    -.006756f,5.466e-4f,-3.835e-4f,-8.9e-4f,0.f,.01326f,.01172f,
	    .002924f,-7.493e-4f,-.03087f,-.05013f,-.0347f,-.06555f,-.07123f,
	    -.05683f,-.09981f,-.06147f,-.003435f,.002866f,-.004977f,0.f,
	    5.793e-4f,.003593f,-.007838f,-.005636f,-1.107e-4f,.002216f,
	    .00147f,-.001033f,.001537f,.003571f,-1.663e-4f,-.001234f,.002199f,
	    2.412e-4f,-2.823e-6f,0.f,.006914f,.003282f,4.769e-4f,-.001613f,
	    4.115e-4f,.002094f,6.465e-4f,.001674f,-.004173f,.001732f,.004148f,
	    -6.353e-5f,6.061e-4f,.00122f,-1.448e-4f,0.f,1.052e-4f,-4.921e-4f,
	    -.001008f,-2.503e-4f,2.916e-4f,-1.703e-4f,.001401f,2.802e-4f,
	    -5.765e-4f,-.001165f,-9.79e-4f,-1.729e-4f,-.06584f,-.1082f,
	    -.08988f,-.06786f,-.04041f,-.1066f,-.09049f,-.07148f,.004729f,
	    -.004992f,-3.293e-5f,0.f,-.001752f,-.01892f,-.002994f,.005326f,
	    -.001523f,-.004065f,-.001848f,.004193f,-.00542f,.00357f,-.006748f,
	    .004006f,6.689e-4f,.003615f,4.439e-4f,0.f,-.00684f,-8.631e-4f,
	    -9.889e-4f,6.484e-4f,.001031f,-.002738f,-.001263f,-6.448e-4f,
	    8.921e-4f,-.001876f,.001488f,-1.046e-4f,5.398e-4f,-7.177e-4f,
	    3.17e-4f,0.f,-.002228f,-8.414e-5f,-.001154f,-6.034e-4f,-.001924f,
	    2.173e-4f,-6.227e-4f,9.277e-4f,.001428f,.002356f,-8.412e-5f,
	    -9.435e-4f,-.04565f,-.04373f,.01721f,-.01634f,.006635f,-.04259f,
	    -.01302f,-.002385f,.007244f,-.00375f,-.00199f,0.f,-.0048045f,
	    -.00322f,-.004859f,.006853f,-8.543e-5f,.005507f,-4.627e-4f,
	    -.002531f,-.001659f,.004641f,-7.172e-4f,.00151f,.001052f,
	    -.001567f,2.897e-6f,0.f,-9.341e-4f,6.223e-4f,-9.401e-4f,.001319f,
	    -6.696e-4f,-.001458f,-5.454e-4f,1.93e-5f,2.23e-4f,-.00168f,
	    9.101e-4f,9.049e-5f,-7.492e-4f,-7.397e-4f,3.385e-4f,0.f,
	    -9.995e-4f,-1.243e-4f,-1.735e-4f,-1.999e-4f,.04405f,.07903f,
	    .08432f,.0528f,.04285f,.07393f,.07055f,.03976f,.003047f,.004131f,
	    -.001951f,0.f,-5.211e-4f,-.003143f,.006398f,.002802f,.002858f,
	    .003714f,.001487f,.002438f,-.003293f,-.002362f,-.003103f,-.00103f,
	    -1.465e-4f,.001073f,.001042f,0.f,.00179f,.001235f,-9.38e-4f,
	    5.599e-4f,.001195f,-8.991e-4f,-4.788e-4f,-5.292e-4f,6.435e-4f,
	    -.001551f,-4e-4f,-4.791e-4f,-1.024e-4f,2.976e-4f,-1.276e-4f,0.f,
	    -1.891e-4f,2.099e-4f,-.001165f,-8.46e-5f,.04582f,.02623f,.02373f,
	    .01555f,.03844f,.02299f,.02713f,.02683f,8.749e-4f,.002344f,
	    .002409f,0.f,.00359f,.005301f,-.001654f,.00427f,3.011e-4f,
	    5.608e-4f,5.263e-4f,-.003259f,-8.139e-4f,-.004306f,.002781f,
	    5.911e-4f,4.473e-4f,4.124e-4f,.001301f,0.f,-.001996f,-.001303f,
	    -5.215e-6f,2.987e-4f,-2.782e-4f,1.509e-4f,-4.177e-4f,-5.998e-4f,
	    2.398e-4f,7.687e-6f,2.258e-4f,-2.08e-4f,.04911f,.05103f,.03974f,
	    .03168f,.02938f,.05305f,.05022f,.01396f,-.01016f,.00345f,
	    1.418e-4f,0.f,.00761f,.006642f,.0095f,-.001922f,.0027f,.001283f,
	    -.001048f,.002382f,.00347655f,-.001686f,4.147e-4f,-.001063f,
	    -9.304e-4f,7.238e-4f,-2.982e-4f,0.f,.001707f,.001048f,3.499e-4f,
	    3.803e-4f,-.001202f,-3.464e-5f,-3.396e-5f,-4.078e-4f,2.769e-4f,
	    5.958e-4f,-6.097e-4f,1.343e-4f,.0221f,.01663f,.0131f,.02312f,
	    -.0157f,.04341f,.04118f,.01771f,.002566f,-.001644f,.001413f,0.f,
	    9.83e-4f,-8.819e-5f,.006556f,-.001038f,-1.22e-4f,-7.1e-4f,
	    -1.373e-4f,1.481e-4f,-6.532e-4f,-3.33e-4f,.003793f,-4.645e-4f,
	    3.987e-4f,5.281e-4f,2.638e-4f,0.f,9.29e-5f,-2.158e-4f,-1.226e-4f,
	    -2.481e-4f,-.05744f,-.02729f,-.04171f,-.01885f,-.02506f,-.04106f,
	    -.02517f,-.02251f,.004408f,.003556f,-5.932e-4f,0.f,.004681f,
	    .004191f,1.491e-4f,-.0029f,-.003497f,-.003391f,-7.523e-4f,
	    .001144f,.001461f,.002045f,.001075f,-3.977e-4f,8.3e-4f,-1.787e-4f,
	    -6.883e-4f,0.f,-3.757e-6f,-1.437e-4f,4.531e-4f,-5.16e-4f,-.03536f,
	    .002154f,-.02355f,-.009952f,-.009728f,-.01803f,-.009012f,
	    -.008079f,-.008813f,.006476f,5.695e-4f,0.f,.002315f,-8.072e-4f,
	    .003343f,-.001528f,.002423f,-8.282e-4f,-2.219e-5f,-5.51e-4f,
	    6.377e-4f,-4.24e-4f,.003431f,3.06e-4f,-.02994f,-.02361f,-.02301f,
	    -.0202f,-.01705f,-.026f,-.02519f,-.01582f,-.001929f,9.557e-4f,
	    -9.962e-5f,0.f,.002767f,-.002329f,3.793e-5f,-8.536e-4f,-5.268e-4f,
	    3.205e-4f,-6.761e-4f,-7.283e-5f,-6.992e-4f,5.949e-4f,5.973e-4f,
	    1.565e-4f,-.02228f,-.02301f,.00204f,-.01272f,-.0115f,-.01371f,
	    -.01423f,-.01252f,.003385f,-8.54e-4f,-5.479e-4f,0.f,-.001644f,
	    -.002188f,-.00132f,2.319e-4f,.0413f,-.01126f,.02591f,.002224f,
	    .003355f,.01788f,-.006048f,.004311f,.004876f,-.002323f,-.002425f,
	    0.f,-.004326f,6.405e-4f,-.005005f,.001024f,.02692f,-.008582f,
	    .01583f,-.00251f,.02035f,.005977f,-.0115f,1.296e-6f,.001684f,
	    .02683f,.009577f,.02434f,.02985f,.01333f,.02574f,.0179f };

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static real a[82];
    static integer i__, j, k;
    static real az;
    static integer is;
    static real ste;
    static integer kend;
    static real colat;
    extern /* Subroutine */ int spharm_(real *, integer *, integer *, real *, 
	    real *);

/* CALCULATES ELECTRON TEMPERATURES TE(1) TO TE(4) AT ALTITUDES */
/* 300, 400, 1400 AND 3000 KM FOR DIP-LATITUDE DIPL/DEG AND */
/* LOCAL SOLAR TIME SLT/H USING THE BRACE-THEIS-MODELS (J. ATMOS. */
/* TERR. PHYS. 43, 1317, 1981); NS IS SEASON IN NORTHERN */
/* HEMISOHERE: IS=1 SPRING, IS=2 SUMMER .... */
/* ALSO CALCULATED ARE THE TEMPERATURES AT 400 KM ALTITUDE FOR */
/* MIDNIGHT (TE(5)) AND NOON (TE(6)). */
    /* Parameter adjustments */
    --te;

    /* Function Body */
    if (*ns < 3) {
	is = *ns;
    } else if (*ns > 3) {
	is = 2;
	*dipl = -(*dipl);
    } else {
	is = 1;
    }
    colat = const_1.umr * (90.f - *dipl);
    az = *slt * .2618f;
    spharm_(a, &c__8, &c__8, &colat, &az);
    if (is == 2) {
	kend = 3;
    } else {
	kend = 4;
    }
    i__1 = kend;
    for (k = 1; k <= i__1; ++k) {
	ste = 0.f;
	for (i__ = 1; i__ <= 81; ++i__) {
/* L1: */
	    ste += a[i__ - 1] * c__[k + (is + (i__ << 1) << 2) - 13];
	}
/* L2: */
	d__1 = (doublereal) ste;
	te[k] = pow_dd(&c_b235, &d__1);
    }
    if (is == 2) {
	*dipl = -(*dipl);
	colat = const_1.umr * (90.f - *dipl);
	spharm_(a, &c__8, &c__8, &colat, &az);
	ste = 0.f;
	for (i__ = 1; i__ <= 81; ++i__) {
/* L11: */
	    ste += a[i__ - 1] * c__[((i__ << 1) + 2 << 2) - 9];
	}
	d__1 = (doublereal) ste;
	te[4] = pow_dd(&c_b235, &d__1);
    }
/* ---------- TEMPERATURE AT 400KM AT MIDNIGHT AND NOON */
    for (j = 1; j <= 2; ++j) {
	ste = 0.f;
	az = (j - 1) * .2618f * 12.f;
	spharm_(a, &c__8, &c__8, &colat, &az);
	for (i__ = 1; i__ <= 81; ++i__) {
/* L3: */
	    ste += a[i__ - 1] * c__[(is + (i__ << 1) << 2) - 11];
	}
/* L4: */
	d__1 = (doublereal) ste;
	te[j + 4] = pow_dd(&c_b235, &d__1);
    }
    return 0;
} /* teba_ */


/* Subroutine */ int spharm_(real *c__, integer *l, integer *m, real *colat, 
	real *az)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), pow_ri(real *, integer *);

    /* Local variables */
    static integer i__, k, n;
    static real x, y;
    static integer mt;
    static real caz, saz;

/* CALCULATES THE COEFFICIENTS OF THE SPHERICAL HARMONIC */
/* EXPANSION THAT WAS USED FOR THE BRACE-THEIS-MODELS. */
    /* Parameter adjustments */
    --c__;

    /* Function Body */
    c__[1] = 1.f;
    k = 2;
    x = cos(*colat);
    c__[k] = x;
    ++k;
    i__1 = *l;
    for (i__ = 2; i__ <= i__1; ++i__) {
	c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ - 1) * c__[k - 2]) 
		/ i__;
/* L10: */
	++k;
    }
    y = sin(*colat);
    i__1 = *m;
    for (mt = 1; mt <= i__1; ++mt) {
	caz = cos(mt * *az);
	saz = sin(mt * *az);
	c__[k] = pow_ri(&y, &mt);
	++k;
	if (mt == *l) {
	    goto L16;
	}
	c__[k] = c__[k - 1] * x * ((mt << 1) + 1);
	++k;
	if (mt + 1 == *l) {
	    goto L16;
	}
	i__2 = *l;
	for (i__ = mt + 2; i__ <= i__2; ++i__) {
	    c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ + mt - 1) * 
		    c__[k - 2]) / (i__ - mt);
/* L15: */
	    ++k;
	}
L16:
	n = *l - mt + 1;
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    c__[k] = c__[k - n] * caz;
	    c__[k - n] *= saz;
/* L18: */
	    ++k;
	}
/* L20: */
    }
    return 0;
} /* spharm_ */



doublereal elte_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static integer i__;
    static real aa, bb, sum;
    extern doublereal eptr_(real *, real *, real *);

/* ---------------------------------------------------------------- */
/* ELECTRON TEMPERATURE PROFILE BASED ON THE TEMPERATURES AT 120 */
/* HMAX,300,400,600,1400,3000 KM ALTITUDE. INBETWEEN CONSTANT */
/* GRADIENT IS ASSUMED. ARGMAX IS MAXIMUM ARGUMENT ALLOWED FOR */
/* EXP-FUNCTION. */
/* ---------------------------------------------------------------- */

    sum = blote_2.ate1 + blote_2.st[0] * (*h__ - blote_2.ah[0]);
    for (i__ = 1; i__ <= 5; ++i__) {
	aa = eptr_(h__, &blote_2.d__[i__ - 1], &blote_2.ah[i__]);
	bb = eptr_(blote_2.ah, &blote_2.d__[i__ - 1], &blote_2.ah[i__]);
/* L1: */
	sum += (blote_2.st[i__] - blote_2.st[i__ - 1]) * (aa - bb) * 
		blote_2.d__[i__ - 1];
    }
    ret_val = sum;
    return ret_val;
} /* elte_ */



doublereal tede_(real *h__, real *den, real *cov)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real y, yc, acov;

/* ELECTRON TEMEPERATURE MODEL AFTER BRACE,THEIS . */
/* FOR NEG. COV THE MEAN COV-INDEX (3 SOLAR ROT.) IS EXPECTED. */
/* DEN IS THE ELECTRON DENSITY IN M-3. */
    y = (*h__ * 17.01f - 2746.f) * exp(*h__ * -5.122e-4f + (6.094e-12f - *h__ 
	    * 3.353e-14f) * *den) + 1051.f;
    acov = dabs(*cov);
    yc = (acov * .00202f + .117f) / (exp(-(acov - 102.5f) / 5.f) + 1.f) + 1.f;
    if (*cov < 0.f) {
	yc = (acov * .00169f + .123f) / (exp(-(acov - 115.f) / 10.f) + 1.f) + 
		1.f;
    }
    ret_val = y * yc;
    return ret_val;
} /* tede_ */



/* ************************************************************* */
/* **************** ION TEMPERATURE **************************** */
/* ************************************************************* */


doublereal ti_(real *h__)
{
    /* System generated locals */
    integer i__1;
    real ret_val;

    /* Local variables */
    static integer i__;
    static real aa, bb, sum;
    extern doublereal eptr_(real *, real *, real *);

/* ---------------------------------------------------------------- */
/* ION TEMPERATURE FOR HEIGHTS NOT GREATER 1000 KM AND NOT LESS HS */
/* EXPLANATION SEE FUNCTION RPID. */
/* ---------------------------------------------------------------- */
    sum = block8_2.mm[0] * (*h__ - block8_2.hs) + block8_2.tnhs;
    i__1 = block8_2.m - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	aa = eptr_(h__, &block8_2.g[i__ - 1], &block8_2.xsm[i__ - 1]);
	bb = eptr_(&block8_2.hs, &block8_2.g[i__ - 1], &block8_2.xsm[i__ - 1])
		;
/* L100: */
	sum += (block8_2.mm[i__] - block8_2.mm[i__ - 1]) * (aa - bb) * 
		block8_2.g[i__ - 1];
    }
    ret_val = sum;
    return ret_val;
} /* ti_ */



doublereal teder_(real *h__)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal tn_(real *, real *, real *, real *);
    static real tnh, dtdx;
    extern doublereal dtndh_(real *, real *, real *, real *);

/* THIS FUNCTION ALONG WITH PROCEDURE REGFA1 ALLOWS TO FIND */
/* THE  HEIGHT ABOVE WHICH TN BEGINS TO BE DIFFERENT FROM TI */
    tnh = tn_(h__, &blotn_2.tex, &blotn_2.tlbd, &blotn_2.sig);
    dtdx = dtndh_(h__, &blotn_2.tex, &blotn_2.tlbd, &blotn_2.sig);
    ret_val = dtdx * (blotn_2.xsm1 - *h__) + tnh;
    return ret_val;
} /* teder_ */



/* ************************************************************* */
/* ************* ION RELATIVE PRECENTAGE DENSITY ***************** */
/* ************************************************************* */


doublereal rpid_(real *h__, real *h0, real *n0, integer *m, real *st, integer 
	*id, real *xs)
{
    /* System generated locals */
    integer i__1;
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static real aa, bb, sm, xi, sum;
    extern doublereal eptr_(real *, real *, real *);

/* ------------------------------------------------------------------ */
/* D.BILITZA,1977,THIS ANALYTIC FUNCTION IS USED TO REPRESENT THE */
/* RELATIVE PRECENTAGE DENSITY OF ATOMAR AND MOLECULAR OXYGEN IONS. */
/* THE M+1 HEIGHT GRADIENTS ST(M+1) ARE CONNECTED WITH EPSTEIN- */
/* STEP-FUNCTIONS AT THE STEP HEIGHTS XS(M) WITH TRANSITION */
/* THICKNESSES ID(M). RPID(H0,H0,N0,....)=N0. */
/* ARGMAX is the highest allowed argument for EXP in your system. */
/* ------------------------------------------------------------------ */
    /* Parameter adjustments */
    --xs;
    --id;
    --st;

    /* Function Body */
    sum = (*h__ - *h0) * st[1];
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xi = (real) id[i__];
	aa = eptr_(h__, &xi, &xs[i__]);
	bb = eptr_(h0, &xi, &xs[i__]);
/* L100: */
	sum += (st[i__ + 1] - st[i__]) * (aa - bb) * xi;
    }
    if (dabs(sum) < argexp_1.argmax) {
	sm = exp(sum);
    } else if (sum > 0.f) {
	sm = exp(argexp_1.argmax);
    } else {
	sm = 0.f;
    }
    ret_val = *n0 * sm;
    return ret_val;
} /* rpid_ */



/* Subroutine */ int rdhhe_(real *h__, real *hb, real *rdoh, real *rdo2h, 
	real *rno, real *pehe, real *rdh, real *rdhe)
{
    static real rest;

/* BILITZA,FEB.82,H+ AND HE+ RELATIVE PERECENTAGE DENSITY BELOW */
/* 1000 KM. THE O+ AND O2+ REL. PER. DENSITIES SHOULD BE GIVEN */
/* (RDOH,RDO2H). HB IS THE ALTITUDE OF MAXIMAL O+ DENSITY. PEHE */
/* IS THE PRECENTAGE OF HE+ IONS COMPARED TO ALL LIGHT IONS. */
/* RNO IS THE RATIO OF NO+ TO O2+DENSITY AT H=HB. */
    *rdhe = 0.f;
    *rdh = 0.f;
    if (*h__ <= *hb) {
	goto L100;
    }
    rest = 100.f - *rdoh - *rdo2h - *rno * *rdo2h;
    *rdh = rest * (1.f - *pehe / 100.f);
    *rdhe = rest * *pehe / 100.f;
L100:
    return 0;
} /* rdhhe_ */



doublereal rdno_(real *h__, real *hb, real *rdo2h, real *rdoh, real *rno)
{
    /* System generated locals */
    real ret_val;

/* D.BILITZA, 1978. NO+ RELATIVE PERCENTAGE DENSITY ABOVE 100KM. */
/* FOR MORE INFORMATION SEE SUBROUTINE RDHHE. */
    if (*h__ > *hb) {
	goto L200;
    }
    ret_val = 100.f - *rdo2h - *rdoh;
    return ret_val;
L200:
    ret_val = *rno * *rdo2h;
    return ret_val;
} /* rdno_ */



/* Subroutine */ int koefp1_(real *pg1o)
{
    /* Initialized data */

    static real feld[80] = { -11.f,-11.f,4.f,-11.f,.08018f,.13027f,.04216f,
	    .25f,-.00686f,.00999f,5.113f,.1f,170.f,180.f,.1175f,.15f,-11.f,
	    1.f,2.f,-11.f,.069f,.161f,.254f,.18f,.0161f,.0216f,.03014f,.1f,
	    152.f,167.f,.04916f,.17f,-11.f,2.f,2.f,-11.f,.072f,.092f,.014f,
	    .21f,.01389f,.03863f,.05762f,.12f,165.f,168.f,.008f,.258f,-11.f,
	    1.f,3.f,-11.f,.091f,.088f,.008f,.34f,.0067f,.0195f,.04f,.1f,158.f,
	    172.f,.01f,.24f,-11.f,2.f,3.f,-11.f,.083f,.102f,.045f,.03f,
	    .00127f,.01f,.05f,.09f,167.f,185.f,.015f,.18f };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS PG1O FOR CALCULATING  O+ PROFILES */
/* BELOW THE F2-MAXIMUM. CHOSEN TO APPROACH DANILOV- */
/* SEMENOV'S COMPILATION. */
    /* Parameter adjustments */
    --pg1o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 80; ++i__) {
	++k;
/* L10: */
	pg1o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp1_ */



/* Subroutine */ int koefp2_(real *pg2o)
{
    /* Initialized data */

    static real feld[32] = { 1.f,-11.f,-11.f,1.f,695.f,-7.81e-4f,-.00264f,
	    2177.f,1.f,-11.f,-11.f,2.f,570.f,-.002f,-.0052f,1040.f,2.f,-11.f,
	    -11.f,1.f,695.f,-7.86e-4f,-.00165f,3367.f,2.f,-11.f,-11.f,2.f,
	    575.f,-.00126f,-.00524f,1380.f };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS FOR CALCULATION OF O+ PROFILES */
/* ABOVE THE F2-MAXIMUM (DUMBS,SPENNER:AEROS-COMPILATION) */
    /* Parameter adjustments */
    --pg2o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 32; ++i__) {
	++k;
/* L10: */
	pg2o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp2_ */



/* Subroutine */ int koefp3_(real *pg3o)
{
    /* Initialized data */

    static real feld[80] = { -11.f,1.f,2.f,-11.f,160.f,31.f,130.f,-10.f,198.f,
	    0.f,.05922f,-.07983f,-.00397f,8.5e-4f,-.00313f,0.f,-11.f,2.f,2.f,
	    -11.f,140.f,30.f,130.f,-10.f,190.f,0.f,.05107f,-.07964f,9.7e-4f,
	    -.01118f,-.02614f,-.09537f,-11.f,1.f,3.f,-11.f,140.f,37.f,125.f,
	    0.f,182.f,0.f,.0307f,-.04968f,-.00248f,-.02451f,-.00313f,0.f,
	    -11.f,2.f,3.f,-11.f,140.f,37.f,125.f,0.f,170.f,0.f,.02806f,
	    -.04716f,6.6e-4f,-.02763f,-.02247f,-.01919f,-11.f,-11.f,4.f,-11.f,
	    140.f,45.f,136.f,-9.f,181.f,-26.f,.02994f,-.04879f,-.01396f,
	    8.9e-4f,-.09929f,.05589f };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS FOR CALCULATING O2+ PROFILES. */
/* CHOSEN AS TO APPROACH DANILOV-SEMENOV'S COMPILATION. */
    /* Parameter adjustments */
    --pg3o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 80; ++i__) {
	++k;
/* L10: */
	pg3o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp3_ */



/* Subroutine */ int sufe_(real *field, real *rfe, integer *m, real *fe)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static real efe[4];

/* SELECTS THE REQUIRED ION DENSITY PARAMETER SET. */
/* THE INPUT FIELD INCLUDES DIFFERENT SETS OF DIMENSION M EACH */
/* CARACTERISED BY 4 HEADER NUMBERS. RFE(4) SHOULD CONTAIN THE */
/* CHOSEN HEADER NUMBERS.FE(M) IS THE CORRESPONDING SET. */
    /* Parameter adjustments */
    --fe;
    --rfe;
    --field;

    /* Function Body */
    k = 0;
L100:
    for (i__ = 1; i__ <= 4; ++i__) {
	++k;
/* L101: */
	efe[i__ - 1] = field[k];
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++k;
/* L111: */
	fe[i__] = field[k];
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	if (efe[i__ - 1] > -10.f && rfe[i__] != efe[i__ - 1]) {
	    goto L100;
	}
/* L120: */
    }
    return 0;
} /* sufe_ */



/* ************************************************************* */
/* ************* PEAK VALUES ELECTRON DENSITY ****************** */
/* ************************************************************* */


/* Subroutine */ int f2out_(real *xmodip, real *xlati, real *xlongi, real *
	ff0, real *xm0, real *ut, real *fof2, real *xm3000)
{
    /* Initialized data */

    static integer qf[9] = { 11,11,8,4,1,0,0,0,0 };
    static integer qm[7] = { 6,7,5,2,1,0,0 };

    extern doublereal gamma1_(real *, real *, real *, real *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, real *);

/* CALCULATES FOF2/MHZ AND M3000 USING THE CCIR-MAPS. */
/* INPUT: MODIFIED DIP LATITUDE XMODIP, GEOG. LATITUDE XLATI, */
/* LONGITUDE XLONGI (ALL IN DEG.), SMOOTHED SUNSPOT NUMBER R, */
/* MONTH AND UNIVERSAL TIME UT (DEC. HOURS). */
/* D.BILITZA,JULY 85. */
    /* Parameter adjustments */
    --xm0;
    --ff0;

    /* Function Body */
    *fof2 = gamma1_(xmodip, xlati, xlongi, ut, &c__6, qf, &c__9, &c__76, &
	    c__13, &c__988, &ff0[1]);
    *xm3000 = gamma1_(xmodip, xlati, xlongi, ut, &c__4, qm, &c__7, &c__49, &
	    c__9, &c__441, &xm0[1]);
    return 0;
} /* f2out_ */



doublereal hmf2ed_(real *xmagbr, real *r__, real *x, real *xm3)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real f1, f2, f3, delm;

/* CALCULATES THE PEAK HEIGHT HMF2/KM FOR THE MAGNETIC */
/* LATITUDE XMAGBR/DEG. AND THE SMOOTHED ZUERICH SUNSPOT */
/* NUMBER R USING CCIR-M3000 XM3 AND THE RATIO X=FOF2/FOE. */
/* [REF. D.BILITZA ET AL., TELECOMM.J., 46, 549-553, 1979] */
/* D.BILITZA,1980. */
    f1 = *r__ * .00232f + .222f;
    f2 = 1.2f - exp(*r__ * .0239f) * .0116f;
    f3 = (*r__ - 25.f) * .096f / 150.f;
    delm = f1 * (1.f - *r__ / 150.f * exp(-(*xmagbr) * *xmagbr / 1600.f)) / (*
	    x - f2) + f3;
    ret_val = 1490.f / (*xm3 + delm) - 176.f;
    return ret_val;
} /* hmf2ed_ */



doublereal fof1ed_(real *ylati, real *r__, real *chi)
{
    /* System generated locals */
    real ret_val;
    doublereal d__1, d__2;

    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static real f0, fs, f100, dla, chi0, fof1, chim, xmue, chi100;

/* -------------------------------------------------------------- */
/* CALCULATES THE F1 PEAK PLASMA FREQUENCY (FOF1/MHZ) */
/* FOR 	DIP-LATITUDE (YLATI/DEGREE) */
/* 	SMOOTHED ZURICH SUNSPOT NUMBER (R) */
/* 	SOLAR ZENITH ANGLE (CHI/DEGREE) */
/* REFERENCE: */
/* 	E.D.DUCHARME ET AL., RADIO SCIENCE 6, 369-378, 1971 */
/* 				       AND 8, 837-839, 1973 */
/* 	HOWEVER WITH MAGNETIC DIP LATITUDE INSTEAD OF GEOMAGNETIC */
/* 	DIPOLE LATITUDE, EYFRIG, 1979 */
/* --------------------------------------------- D. BILITZA, 1988. */
    fof1 = 0.f;
    dla = *ylati;
    chi0 = dla * .349504f + 49.84733f;
    chi100 = dla * .509932f + 38.96113f;
    chim = chi0 + (chi100 - chi0) * *r__ / 100.f;
    if (*chi > chim) {
	goto L1;
    }
    f0 = dla * (.0058f - dla * 1.2e-4f) + 4.35f;
    f100 = dla * (.011f - dla * 2.3e-4f) + 5.348f;
    fs = f0 + (f100 - f0) * *r__ / 100.f;
    xmue = dla * (.0046f - dla * 5.4e-5f) + .093f + *r__ * 3e-4f;
    d__1 = (doublereal) cos(*chi * const_1.umr);
    d__2 = (doublereal) xmue;
    fof1 = fs * pow_dd(&d__1, &d__2);
L1:
    ret_val = fof1;
    return ret_val;
} /* fof1ed_ */



doublereal foeedi_(real *cov, real *xhi, real *xhim, real *xlati)
{
    /* System generated locals */
    real ret_val;
    doublereal d__1, d__2;

    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *), exp(
	    doublereal), log(doublereal);

    /* Local variables */
    static real a, b, c__, d__, sl, sm, sp, xhic, smin, r4foe;

/* ------------------------------------------------------- */
/* CALCULATES FOE/MHZ BY THE EDINBURGH-METHOD. */
/* INPUT: MEAN 10.7CM SOLAR RADIO FLUX (COV), GEOGRAPHIC */
/* LATITUDE (XLATI/DEG), SOLAR ZENITH ANGLE (XHI/DEG AND */
/* XHIM/DEG AT NOON). */
/* REFERENCE: */
/* 	KOURIS-MUGGELETON, CCIR DOC. 6/3/07, 1973 */
/* 	TROST, J. GEOPHYS. RES. 84, 2736, 1979 (was used */
/* 		to improve the nighttime varition) */
/* D.BILITZA--------------------------------- AUGUST 1986. */
/* variation with solar activity (factor A) ............... */
    a = (*cov - 66.f) * .0094f + 1.f;
/* variation with noon solar zenith angle (B) and with latitude (C) */
    sl = cos(*xlati * const_1.umr);
    if (*xlati < 32.f) {
	sm = sl * 1.92f - 1.93f;
	c__ = sl * 116.f + 23.f;
    } else {
	sm = .11f - sl * .49f;
	c__ = sl * 35.f + 92.f;
    }
    if (*xhim >= 90.f) {
	*xhim = 89.999f;
    }
    d__1 = (doublereal) cos(*xhim * const_1.umr);
    d__2 = (doublereal) sm;
    b = pow_dd(&d__1, &d__2);
/* variation with solar zenith angle (D) .......................... */
    if (*xlati > 12.f) {
	sp = 1.2f;
    } else {
	sp = 1.31f;
    }
/* adjusted solar zenith angle during nighttime (XHIC) ............. */
    xhic = *xhi - log(exp((*xhi - 89.98f) / 3.f) + 1.f) * 3.f;
    d__1 = (doublereal) cos(xhic * const_1.umr);
    d__2 = (doublereal) sp;
    d__ = pow_dd(&d__1, &d__2);
/* determine foE**4 ................................................ */
    r4foe = a * b * c__ * d__;
/* minimum allowable foE (sqrt[SMIN])............................... */
    smin = (*cov - 60.f) * .0015f + .121f;
    smin *= smin;
    if (r4foe < smin) {
	r4foe = smin;
    }
    d__1 = (doublereal) r4foe;
    ret_val = pow_dd(&d__1, &c_b289);
    return ret_val;
} /* foeedi_ */



doublereal xmded_(real *xhi, real *r__, real *yw)
{
    /* System generated locals */
    real ret_val;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *), r_sign(real *,
	     real *), acos(doublereal), cos(doublereal), exp(doublereal);

    /* Local variables */
    static real x, y, z__, xxhi, suxhi;

/* D. BILITZA, 1978, CALCULATES ELECTRON DENSITY OF D MAXIMUM. */
/* XHI/DEG. IS SOLAR ZENITH ANGLE, R SMOOTHED ZURICH SUNSPOT NUMBER */
/* AND YW/M-3 THE ASSUMED CONSTANT NIGHT VALUE. */
/* [REF.: D.BILITZA, WORLD DATA CENTER A REPORT UAG-82,7, */
/*       BOULDER,1981] */
    y = *r__ * 8.8e6f + 6.05e8f;
    d__1 = (doublereal) (-.1f / log(*yw / y));
    z__ = pow_dd(&d__1, &c_b291);
    if (dabs(z__) > 1.f) {
	z__ = r_sign(&c_b84, &z__);
    }
    suxhi = acos(z__);
    if (suxhi < 1.0472f) {
	suxhi = 1.0472f;
    }
    xxhi = *xhi * const_1.umr;
    if (xxhi > suxhi) {
	goto L100;
    }
    x = cos(xxhi);
    d__1 = (doublereal) x;
    ret_val = y * exp(-.1f / pow_dd(&d__1, &c_b294));
    return ret_val;
L100:
    ret_val = *yw;
    return ret_val;
} /* xmded_ */



doublereal gamma1_(real *smodip, real *slat, real *slong, real *hour, integer 
	*iharm, integer *nq, integer *k1, integer *m, integer *mm, integer *
	m3, real *sfe)
{
    /* System generated locals */
    integer i__1, i__2;
    real ret_val;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static doublereal c__[12];
    static integer i__, j, l;
    static doublereal s[12];
    static real s0, s1, s2, s3;
    static integer mi, np;
    static real ss, hou;
    static doublereal sum, coef[100];
    static integer index;
    static real xsinx[13];

/* CALCULATES GAMMA1=FOF2 OR M3000 USING CCIR NUMERICAL MAP */
/* COEFFICIENTS SFE(M3) FOR MODIFIED DIP LATITUDE (SMODIP/DEG) */
/* GEOGRAPHIC LATITUDE (SLAT/DEG) AND LONGITUDE (SLONG/DEG) */
/* AND UNIVERSIAL TIME (HOUR/DECIMAL HOURS). */
/* NQ(K1) IS AN INTEGER ARRAY GIVING THE HIGHEST DEGREES IN */
/* LATITUDE FOR EACH LONGITUDE HARMONIC. */
/* M=1+NQ1+2(NQ2+1)+2(NQ3+1)+... . */
/* SHEIKH,4.3.77. */
    /* Parameter adjustments */
    --nq;
    --sfe;

    /* Function Body */
    hou = (*hour * 15.f - 180.f) * const_1.umr;
    s[0] = sin(hou);
    c__[0] = cos(hou);
    i__1 = *iharm;
    for (i__ = 2; i__ <= i__1; ++i__) {
	c__[i__ - 1] = c__[0] * c__[i__ - 2] - s[0] * s[i__ - 2];
	s[i__ - 1] = c__[0] * s[i__ - 2] + s[0] * c__[i__ - 2];
/* L250: */
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	mi = (i__ - 1) * *mm;
	coef[i__ - 1] = sfe[mi + 1];
	i__2 = *iharm;
	for (j = 1; j <= i__2; ++j) {
	    coef[i__ - 1] = coef[i__ - 1] + sfe[mi + (j << 1)] * s[j - 1] + 
		    sfe[mi + (j << 1) + 1] * c__[j - 1];
/* L300: */
	}
    }
    sum = coef[0];
    ss = sin(*smodip * const_1.umr);
    s3 = ss;
    xsinx[0] = 1.f;
    index = nq[1];
    i__2 = index;
    for (j = 1; j <= i__2; ++j) {
	sum += coef[j] * ss;
	xsinx[j] = ss;
	ss *= s3;
/* L350: */
    }
    xsinx[nq[1] + 1] = ss;
    np = nq[1] + 1;
    ss = cos(*slat * const_1.umr);
    s3 = ss;
    i__2 = *k1;
    for (j = 2; j <= i__2; ++j) {
	s0 = *slong * (j - 1.f) * const_1.umr;
	s1 = cos(s0);
	s2 = sin(s0);
	index = nq[j] + 1;
	i__1 = index;
	for (l = 1; l <= i__1; ++l) {
	    ++np;
	    sum += coef[np - 1] * xsinx[l - 1] * ss * s1;
	    ++np;
	    sum += coef[np - 1] * xsinx[l - 1] * ss * s2;
/* L450: */
	}
	ss *= s3;
/* L400: */
    }
    ret_val = sum;
    return ret_val;
} /* gamma1_ */



/* ************************************************************ */
/* *************** EARTH MAGNETIC FIELD *********************** */
/* ************************************************************** */


/* Subroutine */ int ggm_(integer *art, real *long__, real *lati, real *mlong,
	 real *mlat)
{
    /* Builtin functions */
    double cos(doublereal), sin(doublereal), r_sign(real *, real *), asin(
	    doublereal), acos(doublereal);

    /* Local variables */
    static real ci, si, cbg, cbm, clg, clm, sbg, sbm, slg, slm, ylg, zpi;

/* CALCULATES GEOMAGNETIC LONGITUDE (MLONG) AND LATITUDE (MLAT) */
/* FROM GEOGRAFIC LONGITUDE (LONG) AND LATITUDE (LATI) FOR ART=0 */
/* AND REVERSE FOR ART=1. ALL ANGLES IN DEGREE. */
/* LATITUDE:-90 TO 90. LONGITUDE:0 TO 360 EAST. */
    zpi = const_2.faktor * 360.f;
    cbg = const_2.faktor * 11.4f;
    ci = cos(cbg);
    si = sin(cbg);
    if (*art == 0) {
	goto L10;
    }
    cbm = cos(*mlat * const_2.faktor);
    sbm = sin(*mlat * const_2.faktor);
    clm = cos(*mlong * const_2.faktor);
    slm = sin(*mlong * const_2.faktor);
    sbg = sbm * ci - cbm * clm * si;
    if (dabs(sbg) > 1.f) {
	sbg = r_sign(&c_b84, &sbg);
    }
    *lati = asin(sbg);
    cbg = cos(*lati);
    slg = cbm * slm / cbg;
    clg = (sbm * si + cbm * clm * ci) / cbg;
    if (dabs(clg) > 1.f) {
	clg = r_sign(&c_b84, &clg);
    }
    *long__ = acos(clg);
    if (slg < 0.f) {
	*long__ = zpi - *long__;
    }
    *lati /= const_2.faktor;
    *long__ /= const_2.faktor;
    *long__ += -69.8f;
    if (*long__ < 0.f) {
	*long__ += 360.f;
    }
    return 0;
L10:
    ylg = *long__ + 69.8f;
    cbg = cos(*lati * const_2.faktor);
    sbg = sin(*lati * const_2.faktor);
    clg = cos(ylg * const_2.faktor);
    slg = sin(ylg * const_2.faktor);
    sbm = sbg * ci + cbg * clg * si;
    if (dabs(sbm) > 1.f) {
	sbm = r_sign(&c_b84, &sbm);
    }
    *mlat = asin(sbm);
    cbm = cos(*mlat);
    slm = cbg * slg / cbm;
    clm = (-sbg * si + cbg * clg * ci) / cbm;
    if (dabs(clm) > 1.f) {
	clm = r_sign(&c_b84, &clm);
    }
    *mlong = acos(clm);
    if (slm < 0.f) {
	*mlong = zpi - *mlong;
    }
    *mlat /= const_2.faktor;
    *mlong /= const_2.faktor;
    return 0;
} /* ggm_ */



/* Subroutine */ int fieldg_(real *dlat, real *dlong, real *alt, real *x, 
	real *y, real *z__, real *f, real *dip, real *dec, real *smodip)
{
    /* Initialized data */

    static real fel1[72] = { 0.f,.1506723f,.0101742f,-.0286519f,.0092606f,
	    -.0130846f,.0089594f,-.0136808f,-1.508e-4f,-.0093977f,.013065f,
	    .002052f,-.0121956f,-.0023451f,-.0208555f,.0068416f,-.0142659f,
	    -.0093322f,-.0021364f,-.007891f,.0045586f,.0128904f,-2.951e-4f,
	    -.0237245f,.0289493f,.0074605f,-.0105741f,-5.116e-4f,-.0105732f,
	    -.0058542f,.0033268f,.0078164f,.0211234f,.0099309f,.0362792f,
	    -.020107f,-.004635f,-.0058722f,.0011147f,-.0013949f,-.0108838f,
	    .0322263f,-.014739f,.0031247f,.0111986f,-.0109394f,.0058112f,
	    .2739046f,-.0155682f,-.0253272f,.0163782f,.020573f,.0022081f,
	    .0112749f,-.0098427f,.0072705f,.0195189f,-.0081132f,-.0071889f,
	    -.057997f,-.0856642f,.188426f,-.7391512f,.1210288f,-.0241888f,
	    -.0052464f,-.0096312f,-.0044834f,.0201764f,.0258343f,.0083033f,
	    .0077187f };
    static real fel2[72] = { .0586055f,.0102236f,-.0396107f,-.016786f,
	    -.2019911f,-.5810815f,.0379916f,3.7508268f,1.813303f,-.056425f,
	    -.0557352f,.1335347f,-.0142641f,-.1024618f,.0970994f,-.075183f,
	    -.1274948f,.0402073f,.038629f,.1883088f,.183896f,-.7848989f,
	    .7591817f,-.9302389f,-.856096f,.663325f,-4.6363869f,-13.2599277f,
	    .1002136f,.0855714f,-.0991981f,-.0765378f,-.0455264f,.1169326f,
	    -.2604067f,.1800076f,-.2223685f,-.6347679f,.5334222f,-.3459502f,
	    -.1573697f,.8589464f,1.781599f,-6.3347645f,-3.1513653f,-9.992775f,
	    13.3327637f,-35.4897308f,37.3466339f,-.5257398f,.0571474f,
	    -.5421217f,.240477f,-.1747774f,-.3433644f,.4829708f,.3935944f,
	    .4885033f,.8488121f,-.7640999f,-1.8884945f,3.2930784f,-7.3497229f,
	    .1672821f,-.2306652f,10.5782146f,12.6031065f,8.6579742f,
	    215.5209961f,-27.141922f,22.3405762f,1108.6394043f };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal), r_sign(real *, 
	    real *), asin(doublereal);

    /* Local variables */
    static real d__, g[144], h__[144];
    static integer i__, k, m;
    static real s, f1, x1, y1, z1;
    static integer ih;
    static real cp;
    static integer il;
    static real ct, xi[3], sp, rq, st, xt, rho, xxx, yyy, brh0, zzz;
    static integer imax;
    static real rlat;
    static integer nmax, last, ihmax;
    static real rlong, zdivf, ydivs, dipdiv;

/* THIS IS A SPECIAL VERSION OF THE POGO 68/10 MAGNETIC FIELD */
/* LEGENDRE MODEL. TRANSFORMATION COEFF. G(144) VALID FOR 1973. */
/* INPUT: DLAT, DLONG=GEOGRAPHIC COORDINATES/DEG.(-90/90,0/360), */
/*        ALT=ALTITUDE/KM. */
/* OUTPUT: F TOTAL FIELD (GAUSS), Z DOWNWARD VERTICAL COMPONENT */
/*        X,Y COMPONENTS IN THE EQUATORIAL PLANE (X TO ZERO LONGITUDE). */
/*        DIP INCLINATION ANGLE(DEGREE). SMODIP RAWER'S MODFIED DIP. */
/* SHEIK,1977. */
    k = 0;
    for (i__ = 1; i__ <= 72; ++i__) {
	++k;
	g[k - 1] = fel1[i__ - 1];
/* L10: */
	g[k + 71] = fel2[i__ - 1];
    }
    rlat = *dlat * const_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    nmax = 11;
    d__ = sqrt(40680925.f - ct * 272336.f * ct);
    rlong = *dlong * const_1.umr;
    cp = cos(rlong);
    sp = sin(rlong);
    zzz = (*alt + 40408589.f / d__) * ct / 6371.2f;
    rho = (*alt + 40680925.f / d__) * st / 6371.2f;
    xxx = rho * cp;
    yyy = rho * sp;
    rq = 1.f / (xxx * xxx + yyy * yyy + zzz * zzz);
    xi[0] = xxx * rq;
    xi[1] = yyy * rq;
    xi[2] = zzz * rq;
    ihmax = nmax * nmax + 1;
    last = ihmax + nmax + nmax;
    imax = nmax + nmax - 1;
    i__1 = last;
    for (i__ = ihmax; i__ <= i__1; ++i__) {
/* L100: */
	h__[i__ - 1] = g[i__ - 1];
    }
    for (k = 1; k <= 3; k += 2) {
	i__ = imax;
	ih = ihmax;
L300:
	il = ih - i__;
	f1 = 2.f / (i__ - k + 2.f);
	x1 = xi[0] * f1;
	y1 = xi[1] * f1;
	z1 = xi[2] * (f1 + f1);
	i__ += -2;
	if (i__ - 1 < 0) {
	    goto L400;
	}
	if (i__ - 1 == 0) {
	    goto L500;
	}
	i__1 = i__;
	for (m = 3; m <= i__1; m += 2) {
	    h__[il + m] = g[il + m] + z1 * h__[ih + m] + x1 * (h__[ih + m + 2]
		     - h__[ih + m - 2]) - y1 * (h__[ih + m + 1] + h__[ih + m 
		    - 3]);
	    h__[il + m - 1] = g[il + m - 1] + z1 * h__[ih + m - 1] + x1 * (
		    h__[ih + m + 1] - h__[ih + m - 3]) + y1 * (h__[ih + m + 2]
		     + h__[ih + m - 2]);
/* L600: */
	}
L500:
	h__[il + 1] = g[il + 1] + z1 * h__[ih + 1] + x1 * h__[ih + 3] - y1 * (
		h__[ih + 2] + h__[ih - 1]);
	h__[il] = g[il] + z1 * h__[ih] + y1 * h__[ih + 3] + x1 * (h__[ih + 2] 
		- h__[ih - 1]);
L400:
	h__[il - 1] = g[il - 1] + z1 * h__[ih - 1] + (x1 * h__[ih] + y1 * h__[
		ih + 1]) * 2.f;
/* L700: */
	ih = il;
	if (i__ >= k) {
	    goto L300;
	}
/* L200: */
    }
    s = h__[0] * .5f + (h__[1] * xi[2] + h__[2] * xi[0] + h__[3] * xi[1]) * 
	    2.f;
    xt = (rq + rq) * sqrt(rq);
    *x = xt * (h__[2] - s * xxx);
    *y = xt * (h__[3] - s * yyy);
    *z__ = xt * (h__[1] - s * zzz);
    *f = sqrt(*x * *x + *y * *y + *z__ * *z__);
    brh0 = *y * sp + *x * cp;
    *y = *y * cp - *x * sp;
    *x = *z__ * st - brh0 * ct;
    *z__ = -(*z__) * ct - brh0 * st;
    zdivf = *z__ / *f;
    if (dabs(zdivf) > 1.f) {
	zdivf = r_sign(&c_b84, &zdivf);
    }
    *dip = asin(zdivf);
    ydivs = *y / sqrt(*x * *x + *y * *y);
    if (dabs(ydivs) > 1.f) {
	ydivs = r_sign(&c_b84, &ydivs);
    }
    *dec = asin(ydivs);
    dipdiv = *dip / sqrt(*dip * *dip + st);
    if (dabs(dipdiv) > 1.f) {
	dipdiv = r_sign(&c_b84, &dipdiv);
    }
    *smodip = asin(dipdiv);
    *dip /= const_1.umr;
    *dec /= const_1.umr;
    *smodip /= const_1.umr;
    return 0;
} /* fieldg_ */



/* ************************************************************ */
/* *********** INTERPOLATION AND REST *************************** */
/* ************************************************************** */


/* Subroutine */ int regfa1_(real *x11, real *x22, real *fx11, real *fx22, 
	real *eps, real *fw, E_fp f, logical *schalt, real *x)
{
    /* System generated locals */
    real r__1;

    /* Local variables */
    static logical k;
    static real f1, f2;
    static logical l1;
    static real x1, x2, ep;
    static integer ng;
    static real dx, fx;
    static integer lfd;
    static logical links;

/* REGULA-FALSI-PROCEDURE TO FIND X WITH F(X)-FW=0. X1,X2 ARE THE */
/* STARTING VALUES. THE COMUTATION ENDS WHEN THE X-INTERVAL */
/* HAS BECOME LESS THAN EPS . IF SIGN(F(X1)-FW)= SIGN(F(X2)-FW) */
/* THEN SCHALT=.TRUE. */
    *schalt = FALSE_;
    ep = *eps;
    x1 = *x11;
    x2 = *x22;
    f1 = *fx11 - *fw;
    f2 = *fx22 - *fw;
    k = FALSE_;
    ng = 2;
    lfd = 0;
    if (f1 * f2 <= 0.f) {
	goto L200;
    }
    *x = 0.f;
    *schalt = TRUE_;
    return 0;
L200:
    *x = (x1 * f2 - x2 * f1) / (f2 - f1);
    goto L400;
L300:
    l1 = links;
    dx = (x2 - x1) / ng;
    if (! links) {
	dx *= ng - 1;
    }
    *x = x1 + dx;
L400:
    fx = (*f)(x) - *fw;
    ++lfd;
    if (lfd > 20) {
	ep *= 10.f;
	lfd = 0;
    }
    links = f1 * fx > 0.f;
    k = ! k;
    if (links) {
	x1 = *x;
	f1 = fx;
    } else {
	x2 = *x;
	f2 = fx;
    }
    if ((r__1 = x2 - x1, dabs(r__1)) <= ep) {
	goto L800;
    }
    if (k) {
	goto L300;
    }
    if (links && ! l1 || ! links && l1) {
	ng <<= 1;
    }
    goto L200;
L800:
    return 0;
} /* regfa1_ */



/* Subroutine */ int tal_(real *shabr, real *sdelta, real *shbr, real *sdtdh0,
	 logical *aus6, real *spt)
{
    /* Builtin functions */
    double log(doublereal), sqrt(doublereal);

    /* Local variables */
    static real b, c__, z1, z2, z3, z4;

/* CALCULATES THE COEFFICIENTS SPT FOR THE POLYNOMIAL */
/* Y(X)=1+SPT(1)*X**2+SPT(2)*X**3+SPT(3)*X**4+SPT(4)*X**5 */
/* TO FIT THE VALLEY IN Y, REPRESENTED BY: */
/* Y(X=0)=1, THE X VALUE OF THE DEEPEST VALLEY POINT (SHABR), */
/* THE PRECENTAGE DEPTH (SDELTA), THE WIDTH (SHBR) AND THE */
/* DERIVATIVE DY/DX AT THE UPPER VALLEY BOUNDRY (SDTDH0). */
/* IF THERE IS AN UNWANTED ADDITIONAL EXTREMUM IN THE VALLEY */
/* REGION, THEN AUS6=.TRUE., ELSE AUS6=.FALSE.. */
/* FOR -SDELTA THE COEFF. ARE CALCULATED FOR THE FUNCTION */
/* Y(X)=EXP(SPT(1)*X**2+...+SPT(4)*X**5). */
    /* Parameter adjustments */
    --spt;

    /* Function Body */
    z1 = -(*sdelta) / (*shabr * 100.f * *shabr);
    if (*sdelta > 0.f) {
	goto L500;
    }
    *sdelta = -(*sdelta);
    z1 = log(1.f - *sdelta / 100.f) / (*shabr * *shabr);
L500:
    z3 = *sdtdh0 / (*shbr * 2.f);
    z4 = *shabr - *shbr;
    spt[4] = (z1 * (*shbr - *shabr * 2.f) * *shbr + z3 * z4 * *shabr) * 2.f / 
	    (*shabr * *shbr * z4 * z4 * z4);
    spt[3] = z1 * (*shbr * 2.f - *shabr * 3.f) / (*shabr * z4 * z4) - (*shabr 
	    * 2.f + *shbr) * spt[4];
    spt[2] = z1 * -2.f / *shabr - *shabr * 2.f * spt[3] - *shabr * 3.f * *
	    shabr * spt[4];
    spt[1] = z1 - *shabr * (spt[2] + *shabr * (spt[3] + *shabr * spt[4]));
    *aus6 = FALSE_;
    b = spt[3] * 4.f / (spt[4] * 5.f) + *shabr;
    c__ = spt[1] * -2.f / (spt[4] * 5 * *shabr);
    z2 = b * b / 4.f - c__;
    if (z2 < 0.f) {
	goto L300;
    }
    z3 = sqrt(z2);
    z1 = b / 2.f;
    z2 = -z1 + z3;
    if (z2 > 0.f && z2 < *shbr) {
	*aus6 = TRUE_;
    }
    if (dabs(z3) > 1e-15f) {
	goto L400;
    }
    z2 = c__ / z2;
    if (z2 > 0.f && z2 < *shbr) {
	*aus6 = TRUE_;
    }
    return 0;
L400:
    z2 = -z1 - z3;
    if (z2 > 0.f && z2 < *shbr) {
	*aus6 = TRUE_;
    }
L300:
    return 0;
} /* tal_ */



/* ****************************************************************** */
/* ********** ZENITH ANGLE, DAY OF YEAR, TIME *********************** */
/* ****************************************************************** */


/* Subroutine */ int soco_(integer *ld, real *t, real *flat, real *elon, real 
	*declin, real *zenith, real *sunrse, real *sunset)
{
    /* Initialized data */

    static real p1 = .017203534f;
    static real p2 = .034407068f;
    static real p3 = .051610602f;
    static real p4 = .068814136f;
    static real p6 = .103221204f;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), r_sign(real *, real *), acos(
	    doublereal);

    /* Local variables */
    static real a, b, dc, fa, ch, td, te, tf, et, dcl, phi, eqt, cosx, wlon, 
	    secphi, cosphi;

/* -------------------------------------------------------------------- */
/* 	s/r to calculate the solar declination, zenith angle, and */
/* 	sunrise & sunset times  - based on Newbern Smith's algorithm */
/* 	[leo mcnamara, 1-sep-86, last modified 16-jun-87] */
/* 	{dieter bilitza, 30-oct-89, modified for IRI application} */

/* in:	ld	local day of year */
/* 	t	local hour (decimal) */
/* 	flat	northern latitude in degrees */
/* 	elon	east longitude in degrees */

/* out:	declin      declination of the sun in degrees */
/* 	zenith	    zenith angle of the sun in degrees */
/* 	sunrse	    local time of sunrise in hours */
/* 	sunset	    local time of sunset in hours */
/* ------------------------------------------------------------------- */

/* amplitudes of Fourier coefficients  --  1955 epoch................. */

/* s/r is formulated in terms of WEST longitude....................... */
    wlon = 360.f - *elon;

/* time of equinox for 1980........................................... */
    td = *ld + (*t + wlon / 15.f) / 24.f;
    te = td + .9369f;

/* declination of the sun.............................................. */
    dcl = sin(p1 * (te - 82.242f)) * 23.256f + sin(p2 * (te - 44.855f)) * 
	    .381f + sin(p3 * (te - 23.355f)) * .167f - sin(p4 * (te + 11.97f))
	     * .013f + sin(p6 * (te - 10.41f)) * .011f + .339137f;
    *declin = dcl;
    dc = dcl * const_3.dtr;

/* the equation of time................................................ */
    tf = te - .5f;
    eqt = sin(p1 * (tf - 4.f)) * -7.38f - sin(p2 * (tf + 9.f)) * 9.87f + sin(
	    p3 * (tf - 53.f)) * .27f - cos(p4 * (tf - 17.f)) * .2f;
    et = eqt * const_3.dtr / 4.f;

    fa = *flat * const_3.dtr;
    phi = (*t - 12.f) * .26179939f + et;

    a = sin(fa) * sin(dc);
    b = cos(fa) * cos(dc);
    cosx = a + b * cos(phi);
    if (dabs(cosx) > 1.f) {
	cosx = r_sign(&c_b84, &cosx);
    }
    *zenith = acos(cosx) / const_3.dtr;

/* calculate sunrise and sunset times --  at the ground........... */
/* see Explanatory Supplement to the Ephemeris (1961) pg 401...... */
/* sunrise at height h metres is at............................... */
/* 	chi(h) = 90.83 + 0.0347 * sqrt(h)........................ */
/* this includes corrections for horizontal refraction and........ */
/* semi-diameter of the solar disk................................ */
    ch = cos(const_3.dtr * 90.83f);
    cosphi = (ch - a) / b;
/* if abs(secphi) > 1., sun does not rise/set..................... */
/* allow for sun never setting - high latitude summer............. */
    secphi = 999999.f;
    if (cosphi != 0.f) {
	secphi = 1.f / cosphi;
    }
    *sunset = 99.f;
    *sunrse = 99.f;
    if (secphi > -1.f && secphi <= 0.f) {
	return 0;
    }
/* allow for sun never rising - high latitude winter.............. */
    *sunset = -99.f;
    *sunrse = -99.f;
    if (secphi > 0.f && secphi < 1.f) {
	return 0;
    }

    if (cosphi > 1.f) {
	cosphi = r_sign(&c_b84, &cosphi);
    }
    phi = acos(cosphi);
    et /= .26179939f;
    phi /= .26179939f;
    *sunrse = 12.f - phi - et;
    *sunset = phi + 12.f - et;
    if (*sunrse < 0.f) {
	*sunrse += 24.f;
    }
    if (*sunset >= 24.f) {
	*sunset += -24.f;
    }

    return 0;
} /* soco_ */



doublereal hpol_(real *hour, real *tw, real *xnw, real *sa, real *su, real *
	dsa, real *dsu)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal epst_(real *, real *, real *);

/* ------------------------------------------------------- */
/* PROCEDURE FOR SMOOTH TIME-INTERPOLATION USING EPSTEIN */
/* STEP FUNCTION AT SUNRISE (SA) AND SUNSET (SU). THE */
/* STEP-WIDTH FOR SUNRISE IS DSA AND FOR SUNSET DSU. */
/* TW,NW ARE THE DAY AND NIGHT VALUE OF THE PARAMETER TO */
/* BE INTERPOLATED. SA AND SU ARE TIME OF SUNRIES AND */
/* SUNSET IN DECIMAL HOURS. */
/* BILITZA----------------------------------------- 1979. */
    if (dabs(*su) > 25.f) {
	if (*su > 0.f) {
	    ret_val = *tw;
	} else {
	    ret_val = *xnw;
	}
	return ret_val;
    }
    ret_val = *xnw + (*tw - *xnw) * epst_(hour, dsa, sa) + (*xnw - *tw) * 
	    epst_(hour, dsu, su);
    return ret_val;
} /* hpol_ */



/* Subroutine */ int moda_(integer *in, integer *month, integer *iday, 
	integer *idoy)
{
    /* Initialized data */

    static integer mo[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

    static integer imo, mobe, moold;

/* ------------------------------------------------------------------- */
/* CALCULATES DAY OF YEAR (IDOY) FROM MONTH (MONTH) AND DAY (IDAY) */
/* IF IN=0, OR MONTH (MONTH) AND DAY (IDAY) FROM DAY OF */
/* YEAR (IDOY), IF IN=1. */
/* ------------------------------------------------------------------- */
    imo = 0;
    mobe = 0;
    if (*in > 0) {
	goto L5;
    }
    *idoy = mo[*month - 1] + *iday;
    return 0;
L5:
    ++imo;
    moold = mobe;
    if (imo > 12) {
	goto L55;
    }
    mobe = mo[imo - 1];
    if (mobe < *idoy) {
	goto L5;
    }
L55:
    *month = imo - 1;
    *iday = *idoy - moold;
    return 0;
} /* moda_ */



doublereal b0pol_(real *hour, real *sax, real *sux, integer *iseason, real *
	r__, real *dela)
{
    /* Initialized data */

    static real b0f[32]	/* was [2][4][2][2] */ = { 114.f,64.f,134.f,77.f,
	    128.f,66.f,75.f,73.f,113.f,115.f,150.f,116.f,138.f,123.f,94.f,
	    132.f,72.f,84.f,83.f,89.f,75.f,85.f,57.f,76.f,102.f,100.f,120.f,
	    110.f,107.f,103.f,76.f,86.f };

    /* System generated locals */
    real ret_val;

    /* Local variables */
    static integer isl, isr;
    extern doublereal hpol_(real *, real *, real *, real *, real *, real *, 
	    real *);
    static real siph[2], sipl[2], dayval, nitval;

/* ----------------------------------------------------------------- */
/* Interpolation procedure for bottomside thickness parameter B0. */
/* Array B0F(ILT,ISEASON,IR,ILATI) distinguishes between day and */
/* night (ILT=1,2), four seasons (ISEASON=1 spring), low and high */
/* solar activity (IR=1,2), and low and middle modified dip */
/* latitudes (ILATI=1,2). In the DATA statement the first value */
/* corresponds to B0F(1,1,1,1), the second to B0F(2,1,1,1), the */
/* third to B0F(1,2,1,1) and so on. */
/* JUNE 1989 --------------------------------------- Dieter Bilitza */

    for (isr = 1; isr <= 2; ++isr) {
	for (isl = 1; isl <= 2; ++isl) {
	    dayval = b0f[(*iseason + (isr + (isl << 1) << 2) << 1) - 26];
	    nitval = b0f[(*iseason + (isr + (isl << 1) << 2) << 1) - 25];
/* Interpolation day/night with transitions at SAX (sunrise) and SUX (sunset) */
/* L7034: */
	    siph[isl - 1] = hpol_(hour, &dayval, &nitval, sax, sux, &c_b84, &
		    c_b84);
	}
/* Interpolation low/middle modip with transition at 30 degrees modip */
/* L7033: */
	sipl[isr - 1] = siph[0] + (siph[1] - siph[0]) / *dela;
    }
/* Interpolation low/high Rz12: linear from 10 to 100 */
    ret_val = sipl[0] + (sipl[1] - sipl[0]) / 90.f * (*r__ - 10.f);
    return ret_val;
} /* b0pol_ */



/* ********************************************************************* */
/* ************************ EPSTEIN FUNCTIONS ************************** */
/* ********************************************************************* */
/* REF:	H. G. BOOKER, J. ATMOS. TERR. PHYS. 39, 619-623, 1977 */
/* 	K. RAWER, ADV. SPACE RES. 4, #1, 11-15, 1984 */
/* ********************************************************************* */


doublereal rlay_(real *x, real *xm, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real y1, y1m, y2m;
    extern doublereal eptr_(real *, real *, real *), epst_(real *, real *, 
	    real *);

/* -------------------------------------------------------- RAWER  LAYER */
    y1 = eptr_(x, sc, hx);
    y1m = eptr_(xm, sc, hx);
    y2m = epst_(xm, sc, hx);
    ret_val = y1 - y1m - (*x - *xm) * y2m / *sc;
    return ret_val;
} /* rlay_ */



doublereal d1lay_(real *x, real *xm, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal epst_(real *, real *, real *);

/* ------------------------------------------------------------ dLAY/dX */
    ret_val = (epst_(x, sc, hx) - epst_(xm, sc, hx)) / *sc;
    return ret_val;
} /* d1lay_ */



doublereal d2lay_(real *x, real *xm, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal epla_(real *, real *, real *);

/* ---------------------------------------------------------- d2LAY/dX2 */
    ret_val = epla_(x, sc, hx) / (*sc * *sc);
    return ret_val;
} /* d2lay_ */



doublereal eptr_(real *x, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal), log(doublereal);

    /* Local variables */
    static real d1;

/* ------------------------------------------------------------ TRANSITION */
    d1 = (*x - *hx) / *sc;
    if (dabs(d1) < argexp_1.argmax) {
	goto L1;
    }
    if (d1 > 0.f) {
	ret_val = d1;
    } else {
	ret_val = 0.f;
    }
    return ret_val;
L1:
    ret_val = log(exp(d1) + 1.f);
    return ret_val;
} /* eptr_ */



doublereal epst_(real *x, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real d1;

/* -------------------------------------------------------------- STEP */
    d1 = (*x - *hx) / *sc;
    if (dabs(d1) < argexp_1.argmax) {
	goto L1;
    }
    if (d1 > 0.f) {
	ret_val = 1.f;
    } else {
	ret_val = 0.f;
    }
    return ret_val;
L1:
    ret_val = 1.f / (exp(-d1) + 1.f);
    return ret_val;
} /* epst_ */



doublereal epstep_(real *y2, real *y1, real *sc, real *hx, real *x)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal epst_(real *, real *, real *);

/* ---------------------------------------------- STEP FROM Y1 TO Y2 */
    ret_val = *y1 + (*y2 - *y1) * epst_(x, sc, hx);
    return ret_val;
} /* epstep_ */



doublereal epla_(real *x, real *sc, real *hx)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real d0, d1, d2;

/* ------------------------------------------------------------ PEAK */
    d1 = (*x - *hx) / *sc;
    if (dabs(d1) < argexp_1.argmax) {
	goto L1;
    }
    ret_val = 0.f;
    return ret_val;
L1:
    d0 = exp(d1);
    d2 = d0 + 1.f;
    ret_val = d0 / (d2 * d2);
    return ret_val;
} /* epla_ */



doublereal xe2to5_(real *h__, real *hmf2, integer *nl, real *hx, real *sc, 
	real *amp)
{
    /* System generated locals */
    integer i__1;
    real ret_val;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static real sum;
    extern doublereal rlay_(real *, real *, real *, real *);
    static real ylay, zlay;

/* ---------------------------------------------------------------------- */
/* NORMALIZED ELECTRON DENSITY (N/NMF2) FOR THE MIDDLE IONOSPHERE FROM */
/* HME TO HMF2 USING LAY-FUNCTIONS. */
/* ---------------------------------------------------------------------- */
    /* Parameter adjustments */
    --amp;
    --sc;
    --hx;

    /* Function Body */
    sum = 1.f;
    i__1 = *nl;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ylay = amp[i__] * rlay_(h__, hmf2, &sc[i__], &hx[i__]);
	d__1 = (doublereal) ylay;
	zlay = pow_dd(&c_b235, &d__1);
/* L1: */
	sum *= zlay;
    }
    ret_val = sum;
    return ret_val;
} /* xe2to5_ */



doublereal xen_(real *h__, real *hmf2, real *xnmf2, real *hme, integer *nl, 
	real *hx, real *sc, real *amp)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    extern doublereal xe1_(real *), xe6_(real *), xe2to5_(real *, real *, 
	    integer *, real *, real *, real *);

/* ---------------------------------------------------------------------- */
/* ELECTRON DENSITY WITH NEW MIDDLE IONOSPHERE */
/* ---------------------------------------------------------------------- */

    /* Parameter adjustments */
    --amp;
    --sc;
    --hx;

    /* Function Body */
    if (*h__ < *hmf2) {
	goto L100;
    }
    ret_val = xe1_(h__);
    return ret_val;
L100:
    if (*h__ < *hme) {
	goto L200;
    }
    ret_val = *xnmf2 * xe2to5_(h__, hmf2, nl, &hx[1], &sc[1], &amp[1]);
    return ret_val;
L200:
    ret_val = xe6_(h__);
    return ret_val;
} /* xen_ */



/* Subroutine */ int valgul_(real *xhi, real *hvb, real *vwu, real *vwa, real 
	*vdp)
{
    /* Builtin functions */
    double cos(doublereal), log(doublereal);

    /* Local variables */
    static real cs, abc, arl, zzz;

/* --------------------------------------------------------------------- */
/*   CALCULATES E-F VALLEY PARAMETERS; T.L. GULYAEVA, ADVANCES IN */
/*   SPACE RESEARCH 7, #6, 39-48, 1987. */

/* 	INPUT:	XHI	SOLAR ZENITH ANGLE [DEGREE] */

/* 	OUTPUT:	VDP	VALLEY DEPTH  (NVB/NME) */
/* 		VWU	VALLEY WIDTH  [KM] */
/* 		VWA	VALLEY WIDTH  (SMALLER, CORRECTED BY RAWER) */
/* 		HVB	HEIGHT OF VALLEY BASE [KM] */
/* ----------------------------------------------------------------------- */


    cs = cos(const_1.umr * *xhi) + .1f;
    abc = dabs(cs);
    *vdp = cs * .45f / (abc + .1f) + .55f;
    arl = (abc + .1f + cs) / (abc + .1f - cs);
    zzz = log(arl);
    *vwu = 45.f - zzz * 10.f;
    *vwa = 45.f - zzz * 5.f;
    *hvb = 1e3f / (cs * .224f + 7.024f + abc * .966f);
    return 0;
} /* valgul_ */



/* Subroutine */ int rogul_(integer *iday, real *xhi, real *sx, real *gro)
{
    /* Builtin functions */
    double cos(doublereal), exp(doublereal);

    /* Local variables */
    static real xs;

/* --------------------------------------------------------------------- */
/*   CALCULATES RATIO H0.5/HMF2 FOR HALF-DENSITY POINT (NE(H0.5)=0.5*NMF2) */
/*   T.L. GULYAEVA, ADVANCES IN SPACE RESEARCH 7, #6, 39-48, 1987. */

/* 	INPUT:	IDAY	DAY OF YEAR */
/* 		XHI	SOLAR ZENITH ANGLE [DEGREE] */

/* 	OUTPUT:	GRO	RATIO OF HALF DENSITY HEIGHT TO F PEAK HEIGHT */
/* 		SX	SMOOTHLY VARYING SEASON PARAMTER (SX=1 FOR */
/* 			DAY=1; SX=3 FOR DAY=180; SX=2 FOR EQUINOX) */
/* ----------------------------------------------------------------------- */

    *sx = 2.f - cos(*iday * .017214206f);
    xs = (*xhi - *sx * 20.f) / 15.f;
    *gro = .8f - .2f / (exp(xs) + 1.f);
/* same as gro=0.6+0.2/(1+exp(-xs)) */
    return 0;
} /* rogul_ */



/* Subroutine */ int lnglsn_(integer *n, real *a, real *b, logical *aus)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1;

    /* Local variables */
    static integer k, l, m, nn, izg;
    static real hsp, azv[10], amax;
    static integer imax;

/* -------------------------------------------------------------------- */
/* SOLVES QUADRATIC SYSTEM OF LINEAR EQUATIONS: */

/* 	INPUT:	N	NUMBER OF EQUATIONS (= NUMBER OF UNKNOWNS) */
/* 		A(N,N)	MATRIX (LEFT SIDE OF SYSTEM OF EQUATIONS) */
/* 		B(N)	VECTOR (RIGHT SIDE OF SYSTEM) */

/* 	OUTPUT:	AUS	=.TRUE.	  NO SOLUTION FOUND */
/* 			=.FALSE.  SOLUTION IS IN  A(N,J) FOR J=1,N */
/* -------------------------------------------------------------------- */


    /* Parameter adjustments */
    --b;
    a -= 6;

    /* Function Body */
    nn = *n - 1;
    *aus = FALSE_;
    i__1 = *n - 1;
    for (k = 1; k <= i__1; ++k) {
	imax = k;
	l = k;
	izg = 0;
	amax = (r__1 = a[k + k * 5], dabs(r__1));
L110:
	++l;
	if (l > *n) {
	    goto L111;
	}
	hsp = (r__1 = a[l + k * 5], dabs(r__1));
	if (hsp < 1e-8f) {
	    ++izg;
	}
	if (hsp <= amax) {
	    goto L110;
	}
L111:
	if (dabs(amax) >= 1e-10f) {
	    goto L133;
	}
	*aus = TRUE_;
	return 0;
L133:
	if (imax == k) {
	    goto L112;
	}
	i__2 = *n;
	for (l = k; l <= i__2; ++l) {
	    azv[l] = a[imax + l * 5];
	    a[imax + l * 5] = a[k + l * 5];
/* L2: */
	    a[k + l * 5] = azv[l];
	}
	azv[0] = b[imax];
	b[imax] = b[k];
	b[k] = azv[0];
L112:
	if (izg == *n - k) {
	    goto L1;
	}
	amax = 1.f / a[k + k * 5];
	azv[0] = b[k] * amax;
	i__2 = *n;
	for (m = k + 1; m <= i__2; ++m) {
/* L3: */
	    azv[m] = a[k + m * 5] * amax;
	}
	i__2 = *n;
	for (l = k + 1; l <= i__2; ++l) {
	    amax = a[l + k * 5];
	    if (dabs(amax) < 1e-8f) {
		goto L4;
	    }
	    a[l + k * 5] = 0.f;
	    b[l] -= azv[0] * amax;
	    i__3 = *n;
	    for (m = k + 1; m <= i__3; ++m) {
/* L5: */
		a[l + m * 5] -= amax * azv[m];
	    }
L4:
	    ;
	}
L1:
	;
    }
    for (k = *n; k >= 1; --k) {
	amax = 0.f;
	if (k < *n) {
	    i__1 = *n;
	    for (l = k + 1; l <= i__1; ++l) {
/* L7: */
		amax += a[k + l * 5] * a[*n + l * 5];
	    }
	}
	if ((r__1 = a[k + k * 5], dabs(r__1)) < 1e-6f) {
	    a[*n + k * 5] = 0.f;
	} else {
	    a[*n + k * 5] = (b[k] - amax) / a[k + k * 5];
	}
/* L6: */
    }
    return 0;
} /* lnglsn_ */



/* Subroutine */ int lsknm_(integer *n, integer *m, integer *m0, integer *m1, 
	real *hm, real *sc, real *hx, real *w, real *x, real *y, real *var, 
	logical *sing)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, m01;
    static real ali[25]	/* was [5][5] */, bli[5], scm, xli[50]	/* was [5][10]
	     */;
    extern doublereal rlay_(real *, real *, real *, real *), d1lay_(real *, 
	    real *, real *, real *), d2lay_(real *, real *, real *, real *);
    extern /* Subroutine */ int lnglsn_(integer *, real *, real *, logical *);

/* -------------------------------------------------------------------- */
/*   DETERMINES LAY-FUNCTIONS AMPLITUDES FOR A NUMBER OF CONSTRAINTS: */

/* 	INPUT:	N	NUMBER OF AMPLITUDES ( LAY-FUNCTIONS) */
/* 		M	NUMBER OF CONSTRAINTS */
/* 		M0	NUMBER OF POINT CONSTRAINTS */
/* 		M1	NUMBER OF FIRST DERIVATIVE CONSTRAINTS */
/* 		HM	F PEAK ALTITUDE  [KM] */
/* 		SC(N)	SCALE PARAMETERS FOR LAY-FUNCTIONS  [KM] */
/* 		HX(N)	HEIGHT PARAMETERS FOR LAY-FUNCTIONS  [KM] */
/* 		W(M)	WEIGHT OF CONSTRAINTS */
/* 		X(M)	ALTITUDES FOR CONSTRAINTS  [KM] */
/* 		Y(M)	LOG(DENSITY/NMF2) FOR CONSTRAINTS */

/* 	OUTPUT:	VAR(M)	AMPLITUDES */
/* 		SING	=.TRUE.   NO SOLUTION */
/* ------------------------------------------------------------------------ */


    /* Parameter adjustments */
    --var;
    --hx;
    --sc;
    --y;
    --x;
    --w;

    /* Function Body */
    m01 = *m0 + *m1;
    scm = 0.f;
    for (j = 1; j <= 5; ++j) {
	bli[j - 1] = 0.f;
	for (i__ = 1; i__ <= 5; ++i__) {
/* L1: */
	    ali[j + i__ * 5 - 6] = 0.f;
	}
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *m0;
	for (k = 1; k <= i__2; ++k) {
/* L3: */
	    xli[i__ + k * 5 - 6] = rlay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
	i__2 = m01;
	for (k = *m0 + 1; k <= i__2; ++k) {
/* L4: */
	    xli[i__ + k * 5 - 6] = d1lay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
	i__2 = *m;
	for (k = m01 + 1; k <= i__2; ++k) {
/* L5: */
	    xli[i__ + k * 5 - 6] = d2lay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
/* L2: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (k = 1; k <= i__2; ++k) {
	    bli[j - 1] += w[k] * y[k] * xli[j + k * 5 - 6];
	    i__3 = *n;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L6: */
		ali[j + i__ * 5 - 6] += w[k] * xli[i__ + k * 5 - 6] * xli[j + 
			k * 5 - 6];
	    }
	}
/* L7: */
    }
    lnglsn_(n, ali, bli, sing);
    if (! (*sing)) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L8: */
	    var[i__] = ali[*n + i__ * 5 - 6];
	}
    }
    return 0;
} /* lsknm_ */



/* Subroutine */ int inilay_(logical *night, real *xnmf2, real *xnmf1, real *
	xnme, real *vne, real *hmf2, real *hmf1, real *hme, real *hv1, real *
	hv2, real *hhalf, real *hxl, real *scl, real *amp, integer *iqual)
{
    /* Builtin functions */
    double r_lg10(real *);

    /* Local variables */
    static real ww[8], xx[8], yy[8];
    static integer nc0, nc1;
    static real zet, scl0, hfff, xfff;
    extern doublereal epst_(real *, real *, real *);
    static logical ssin;
    static real alg102, hxl1t, alogf, xhalf;
    extern /* Subroutine */ int lsknm_(integer *, integer *, integer *, 
	    integer *, real *, real *, real *, real *, real *, real *, real *,
	     logical *);
    static real alogef;
    static integer numcon, numlay;

/* ------------------------------------------------------------------- */
/* CALCULATES AMPLITUDES FOR LAY FUNCTIONS */
/* D. BILITZA, DECEMBER 1988 */

/* INPUT:	NIGHT	LOGICAL VARIABLE FOR DAY/NIGHT DISTINCTION */
/* 		XNMF2	F2 PEAK ELECTRON DENSITY [M-3] */
/* 		XNMF1	F1 PEAK ELECTRON DENSITY [M-3] */
/* 		XNME	E  PEAK ELECTRON DENSITY [M-3] */
/* 		VNE	ELECTRON DENSITY AT VALLEY BASE [M-3] */
/* 		HMF2	F2 PEAK ALTITUDE [KM] */
/* 		HMF1	F1 PEAK ALTITUDE [KM] */
/* 		HME	E  PEAK ALTITUDE [KM] */
/* 		HV1	ALTITUDE OF VALLEY TOP [KM] */
/* 		HV2	ALTITUDE OF VALLEY BASE [KM] */
/* 		HHALF	ALTITUDE OF HALF-F2-PEAK-DENSITY [KM] */

/* OUTPUT:	HXL(4)	HEIGHT PARAMETERS FOR LAY FUNCTIONS [KM] */
/* 		SCL(4)	SCALE PARAMETERS FOR LAY FUNCTIONS [KM] */
/* 		AMP(4)	AMPLITUDES FOR LAY FUNCTIONS */
/* 		IQUAL	=0 ok, =1 ok using second choice for HXL(1) */
/*                       =2 NO SOLUTION */
/* --------------------------------------------------------------- */

/* constants -------------------------------------------------------- */
    /* Parameter adjustments */
    --amp;
    --scl;
    --hxl;

    /* Function Body */
    numlay = 4;
    nc1 = 2;
    alg102 = r_lg10(&c_b380);

/* constraints: xx == height	yy == log(Ne/NmF2)    ww == weights */
/* ----------------------------------------------------------------- */
    alogf = r_lg10(xnmf2);
    alogef = r_lg10(xnme) - alogf;
    xhalf = *xnmf2 / 2.f;
    xx[0] = *hhalf;
    xx[1] = *hv1;
    xx[2] = *hv2;
    xx[3] = *hme;
    xx[4] = *hme - (*hv2 - *hme);
    yy[0] = -alg102;
    yy[1] = alogef;
    yy[2] = r_lg10(vne) - alogf;
    yy[3] = alogef;
    yy[4] = yy[2];
    yy[6] = 0.f;
    ww[1] = 1.f;
    ww[2] = 2.f;
    ww[3] = 5.f;

/* geometric paramters for LAY ------------------------------------- */
/* difference to earlier version:  HXL(3) = HV2 + SCL(3) */

    scl0 = ((*hmf2 - *hhalf) * .216f + 56.8f) * .7f;
    scl[1] = scl0 * .8f;
    scl[2] = 10.f;
    scl[3] = 9.f;
    scl[4] = 6.f;
    hxl[3] = *hv2;

/* DAY CONDITION-------------------------------------------------- */
/* earlier tested: 	HXL(2) = HMF1 + SCL(2) */

    if (*night) {
	goto L7711;
    }
    numcon = 8;
    hxl[1] = *hmf2 * .9f;
    hxl1t = *hhalf;
    hxl[2] = *hmf1;
    hxl[4] = *hme - scl[4];
    xx[5] = *hmf1;
    xx[6] = *hv2;
    xx[7] = *hme;
    yy[7] = 0.f;
    ww[4] = 1.f;
    ww[6] = 50.f;
    ww[7] = 500.f;
/* without F-region ---------------------------------------------- */
    if (*xnmf1 > 0.f) {
	goto L100;
    }
    hxl[2] = (*hmf2 + *hhalf) / 2.f;
    yy[5] = 0.f;
    ww[5] = 0.f;
    ww[0] = 1.f;
    goto L7722;
/* with F-region -------------------------------------------- */
L100:
    yy[5] = r_lg10(xnmf1) - alogf;
    ww[5] = 3.f;
    if ((*xnmf1 - xhalf) * (*hmf1 - *hhalf) < 0.f) {
	ww[0] = .5f;
    } else {
	zet = yy[0] - yy[5];
	ww[0] = epst_(&zet, &c_b384, &c_b385);
    }
    if (*hhalf > *hmf1) {
	hfff = *hmf1;
	xfff = *xnmf1;
    } else {
	hfff = *hhalf;
	xfff = xhalf;
    }
    goto L7722;

/* NIGHT CONDITION--------------------------------------------------- */
/* different HXL,SCL values were tested including: */
/* 	SCL(1) = HMF2 * 0.15 - 27.1	HXL(2) = 200. */
/* 	HXL(2) = HMF1 + SCL(2)		HXL(3) = 140. */
/*  	SCL(3) = 5.			HXL(4) = HME + SCL(4) */
/* 	HXL(4) = 105. */

L7711:
    numcon = 7;
    hxl[1] = *hhalf;
    hxl1t = *hmf2 * .4f + 30.f;
    hxl[2] = (*hmf2 + *hv1) / 2.f;
    hxl[4] = *hme;
    xx[5] = *hv2;
    xx[6] = *hme;
    yy[5] = 0.f;
    ww[0] = 1.f;
    ww[2] = 3.f;
    ww[4] = .5f;
    ww[5] = 50.f;
    ww[6] = 500.f;
    hfff = *hhalf;
    xfff = xhalf;

/* are valley-top and bottomside point compatible ? ------------- */

L7722:
    if ((*hv1 - hfff) * (*xnme - xfff) < 0.f) {
	ww[1] = .5f;
    }
    if (*hv1 <= *hv2 + 5.f) {
	ww[1] = .5f;
    }

/* DETERMINE AMPLITUDES----------------------------------------- */

    nc0 = numcon - nc1;
    *iqual = 0;
L2299:
    lsknm_(&numlay, &numcon, &nc0, &nc1, hmf2, &scl[1], &hxl[1], ww, xx, yy, &
	    amp[1], &ssin);
    if (*iqual > 0) {
	goto L1937;
    }
    if (dabs(amp[1]) > 10.f || ssin) {
	*iqual = 1;
	hxl[1] = hxl1t;
	goto L2299;
    }
L1937:
    if (ssin) {
	*iqual = 2;
    }
    return 0;
} /* inilay_ */



/* Subroutine */ int ioncom_(real *h__, real *z__, real *f, real *fs, real *t,
	 real *cn)
{
    /* Initialized data */

    static real po[30]	/* was [5][6] */ = { 0.f,0.f,0.f,0.f,98.5f,0.f,0.f,
	    0.f,0.f,320.f,0.f,0.f,0.f,0.f,-2.59e-4f,2.79e-4f,-.00333f,
	    -.00352f,-.00516f,-.0247f,0.f,0.f,0.f,0.f,-2.5e-6f,.00104f,
	    -1.79e-4f,-4.29e-5f,1.01e-5f,-.00127f };
    static real ph[30]	/* was [5][6] */ = { -4.97e-7f,-.121f,-.131f,0.f,
	    98.1f,355.f,-191.f,-127.f,0.f,2040.f,0.f,0.f,0.f,0.f,-4.79e-6f,
	    -2e-4f,5.67e-4f,2.6e-4f,0.f,-.00508f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f };
    static real pn[30]	/* was [5][6] */ = { .76f,-5.62f,-4.99f,0.f,5.79f,
	    83.f,-369.f,-324.f,0.f,593.f,0.f,0.f,0.f,0.f,-6.3e-5f,-.00674f,
	    -.00793f,-.00465f,0.f,-.00326f,0.f,0.f,0.f,0.f,-1.17e-5f,.00488f,
	    -.00131f,-7.03e-4f,0.f,-.00238f };
    static real phe[30]	/* was [5][6] */ = { -.895f,6.1f,5.39f,0.f,8.01f,0.f,
	    0.f,0.f,0.f,1200.f,0.f,0.f,0.f,0.f,-1.04e-5f,.0019f,9.53e-4f,
	    .00106f,0.f,-.00344f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
    static real pno[30]	/* was [5][6] */ = { -22.4f,17.7f,-13.4f,-4.88f,62.3f,
	    32.7f,0.f,19.8f,2.07f,115.f,0.f,0.f,0.f,0.f,0.f,.00394f,0.f,
	    .00248f,2.15e-4f,.00667f,0.f,0.f,0.f,0.f,0.f,-.0084f,0.f,-.00364f,
	    .002f,-.0259f };
    static real po2[30]	/* was [5][6] */ = { 8.f,-12.2f,9.9f,5.8f,53.4f,
	    -25.2f,0.f,-28.5f,-6.72f,120.f,0.f,0.f,0.f,0.f,0.f,-.014f,0.f,
	    -.0093f,.0033f,.028f,0.f,0.f,0.f,0.f,0.f,.00425f,0.f,-.00604f,
	    .00385f,-.0364f };
    static real pcl[30]	/* was [5][6] */ = { 0.f,0.f,0.f,0.f,100.f,0.f,0.f,
	    0.f,0.f,75.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,-.00904f,-.00728f,0.f,0.f,.00346f,-.0211f };

    /* Builtin functions */
    double cos(doublereal), exp(doublereal);

    /* Local variables */
    static integer i__, j;
    static real p[210]	/* was [5][6][7] */, s, cm[7], hm[7], hx, alh[7], all[
	    7], var[6], beth[7], betl[7];

/* --------------------------------------------------------------- */
/* ion composition model */
/* A.D. Danilov and A.P. Yaichnikov, A New Model of the Ion */
/*   Composition at 75 to 1000 km for IRI, Adv. Space Res. 5, #7, */
/*   75-79, 107-108, 1985 */

/* 	h	altitude in km */
/* 	z	solar zenith angle in radians */
/* 	f	latitude in radians */
/* 	fs	10.7cm solar radio flux */
/* 	t	season (month) */
/* 	cn(1)   O+  relative density in percent */
/* 	cn(2)   H+  relative density in percent */
/* 	cn(3)   N+  relative density in percent */
/* 	cn(4)   He+ relative density in percent */
/* 	cn(5)   NO+ relative density in percent */
/* 	cn(6)   O2+ relative density in percent */
/* 	cn(7)   cluster ions  relative density in percent */
/* --------------------------------------------------------------- */

    /* Parameter adjustments */
    --cn;

    /* Function Body */
    for (i__ = 1; i__ <= 5; ++i__) {
	for (j = 1; j <= 6; ++j) {
	    p[i__ + (j + 6) * 5 - 36] = po[i__ + j * 5 - 6];
	    p[i__ + (j + 12) * 5 - 36] = ph[i__ + j * 5 - 6];
	    p[i__ + (j + 18) * 5 - 36] = pn[i__ + j * 5 - 6];
	    p[i__ + (j + 24) * 5 - 36] = phe[i__ + j * 5 - 6];
	    p[i__ + (j + 30) * 5 - 36] = pno[i__ + j * 5 - 6];
	    p[i__ + (j + 36) * 5 - 36] = po2[i__ + j * 5 - 6];
	    p[i__ + (j + 42) * 5 - 36] = pcl[i__ + j * 5 - 6];
/* L8: */
	}
    }
    s = 0.f;
    for (i__ = 1; i__ <= 7; ++i__) {
	for (j = 1; j <= 6; ++j) {
	    var[j - 1] = p[(j + i__ * 6) * 5 - 35] * cos(*z__) + p[(j + i__ * 
		    6) * 5 - 34] * cos(*f) + p[(j + i__ * 6) * 5 - 33] * cos((
		    300.f - *fs) * .013f) + p[(j + i__ * 6) * 5 - 32] * cos((*
		    t - 6.f) * .52f) + p[(j + i__ * 6) * 5 - 31];
/* L7: */
	}
	cm[i__ - 1] = var[0];
	hm[i__ - 1] = var[1];
	all[i__ - 1] = var[2];
	betl[i__ - 1] = var[3];
	alh[i__ - 1] = var[4];
	beth[i__ - 1] = var[5];
	hx = *h__ - hm[i__ - 1];
	if (hx < 0.f) {
	    goto L1;
	} else if (hx == 0) {
	    goto L2;
	} else {
	    goto L3;
	}
L1:
	cn[i__] = cm[i__ - 1] * exp(hx * (hx * all[i__ - 1] + betl[i__ - 1]));
	goto L4;
L2:
	cn[i__] = cm[i__ - 1];
	goto L4;
L3:
	cn[i__] = cm[i__ - 1] * exp(hx * (hx * alh[i__ - 1] + beth[i__ - 1]));
L4:
	if (cn[i__] < cm[i__ - 1] * .005f) {
	    cn[i__] = 0.f;
	}
	if (cn[i__] > cm[i__ - 1]) {
	    cn[i__] = cm[i__ - 1];
	}
	s += cn[i__];
/* L5: */
    }
    for (i__ = 1; i__ <= 7; ++i__) {
/* L6: */
	cn[i__] = cn[i__] / s * 100.f;
    }
    return 0;
} /* ioncom_ */





/* Subroutine */ int cira86_(integer *iday, real *sec, real *glat, real *
	glong, real *stl, real *f107a, real *tinf, real *tlb, real *sigma)
{
    /* Initialized data */

    static real dr = .0172142f;
    static real dr2 = .0344284f;
    static real hr = .2618f;
    static real sr = 7.2722e-5f;
    static real xl = 1e3f;
    static real tll = 1e3f;
    static real dgtr = .0174533f;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static real c__, s, c2, c4, f1, f2, f3, g0, s2, t1, t2, t3, t5, t4, t7, 
	    t8, z1, z2, t11, t12, t14, t71, t72, t81, t82, zz, cd9, cd11, dfa,
	     cd14, cd32, cd18, cd39, plg[36]	/* was [9][4] */, t7814, 
	    ctloc, stloc, c2tloc, c3tloc, s2tloc, s3tloc;

/* ******************************************************************* */
/*   Calculates neutral temperature parameters for IRI using the */
/*   MSIS-86/CIRA 1986 Neutral Thermosphere Model. The subroutines */
/*   GTS5, GLOBE5 and GLOBL5 developed by A.E. Hedin (2/26/87) were */
/*   modified for use in IRI --------- D. Bilitza -------- March 1991 */

/*     INPUT: */
/*        IDAY - DAY OF YEAR */
/*        SEC - UT(SEC) */
/*        GLAT - GEODETIC LATITUDE(DEG) */
/*        GLONG - GEODETIC LONGITUDE(DEG) */
/*        STL - LOCAL APPARENT SOLAR TIME(HRS) */
/*        F107A - 3 MONTH AVERAGE OF F10.7 FLUX */

/*     OUTPUT: */
/*        TINF - EXOSPHERIC TEMPERATURE (K) */
/*        TLB - TEMPERATURE AT LOWER BOUNDARY (K) */
/*        SIGMA - SHAPE PARAMETER FOR TEMPERATURE PROFILE */

/* ********************************************************************** */

/* CALCULATE LEGENDRE POLYNOMIALS */

    if (xl == *glat) {
	goto L15;
    }
    c__ = sin(*glat * dgtr);
    s = cos(*glat * dgtr);
    c2 = c__ * c__;
    c4 = c2 * c2;
    s2 = s * s;
    plg[1] = c__;
    plg[2] = (c2 * 3.f - 1.f) * .5f;
    plg[3] = (c__ * 5.f * c2 - c__ * 3.f) * .5f;
    plg[4] = (c4 * 35.f - c2 * 30.f + 3.f) / 8.f;
    plg[5] = (c2 * 63.f * c2 * c__ - c2 * 70.f * c__ + c__ * 15.f) / 8.f;
    plg[10] = s;
    plg[11] = c__ * 3.f * s;
    plg[12] = (c2 * 5.f - 1.f) * 1.5f * s;
    plg[13] = (c2 * 7.f * c__ - c__ * 3.f) * 2.5f * s;
    plg[14] = (c4 * 21.f - c2 * 14.f + 1.f) * 1.875f * s;
    plg[15] = (c__ * 11.f * plg[14] - plg[13] * 6.f) / 5.f;
    plg[20] = s2 * 3.f;
    plg[21] = s2 * 15.f * c__;
    plg[22] = (c2 * 7.f - 1.f) * 7.5f * s2;
    plg[23] = c__ * 3.f * plg[22] - plg[21] * 2.f;
    plg[30] = s2 * 15.f * s;
    plg[31] = s2 * 105.f * s * c__;
    plg[32] = (c__ * 9.f * plg[31] - plg[30] * 7.f) / 2.f;
    plg[33] = (c__ * 11.f * plg[32] - plg[31] * 8.f) / 3.f;
    xl = *glat;
L15:
    if (tll == *stl) {
	goto L16;
    }
    stloc = sin(hr * *stl);
    ctloc = cos(hr * *stl);
    s2tloc = sin(hr * 2.f * *stl);
    c2tloc = cos(hr * 2.f * *stl);
    s3tloc = sin(hr * 3.f * *stl);
    c3tloc = cos(hr * 3.f * *stl);
    tll = *stl;
L16:

    dfa = *f107a - 150.f;

/* EXOSPHERIC TEMPERATURE */

/*         F10.7 EFFECT */
    t1 = (.00311701f - dfa * 6.4111e-6f) * dfa;
    f1 = dfa * .00426385f + 1.f;
    f2 = dfa * .00511819f + 1.f;
    f3 = dfa * .00292246f + 1.f;
/*        TIME INDEPENDENT */
    t2 = plg[2] * .0385528f + plg[4] * .00303445f;
/*        SYMMETRICAL ANNUAL AND SEMIANNUAL */
    cd14 = cos(dr * (*iday + 8.45398f));
    cd18 = cos(dr2 * (*iday - 125.818f));
    cd32 = cos(dr * (*iday - 30.015f));
    cd39 = cos(dr2 * (*iday - 2.75905f));
    t3 = cd32 * .00805486f + cd18 * .014237f;
/*        ASYMMETRICAL ANNUAL AND SEMIANNUAL */
    t5 = f1 * (plg[1] * -.127371f - plg[3] * .0302449f) * cd14 - plg[1] * 
	    .0192645f * cd39;
/*        DIURNAL */
    t71 = plg[11] * .0123512f * cd14;
    t72 = plg[11] * -.00526277f * cd14;
    t7 = (plg[10] * -.105531f - plg[12] * .00607134f + t71) * ctloc + (plg[10]
	     * -.115622f + plg[12] * .0020224f + t72) * stloc;
/*        SEMIDIURNAL */
    t81 = plg[21] * .00386578f * cd14;
    t82 = plg[21] * .00389146f * cd14;
    t8 = (plg[20] * -5.16278e-4f - plg[22] * .00117388f + t81) * c2tloc + (
	    plg[20] * .00990156f - plg[22] * 3.54589e-4f + t82) * s2tloc;
/*        TERDIURNAL */
    z1 = plg[31] * cd14;
    z2 = plg[33] * cd14;
    t14 = (plg[30] * .00147284f - z1 * 1.73933e-4f + z2 * 3.65016e-5f) * 
	    s3tloc + (plg[30] * 3.41345e-4f - z1 * 1.53218e-4f + z2 * 
	    1.15102e-4f) * c3tloc;
    t7814 = f2 * (t7 + t8 + t14);
/*        LONGITUDINAL */
    t11 = f3 * ((plg[11] * .00562606f + plg[13] * .00594053f + plg[15] * 
	    .00109358f - plg[10] * .00301801f - plg[12] * .00423564f - plg[14]
	     * .00248289f + (plg[10] * .00189689f + plg[12] * .00415654f) * 
	    cd14) * cos(dgtr * *glong) + (plg[11] * -.011654f - plg[13] * 
	    .00449173f - plg[15] * 3.53189e-4f + plg[10] * 9.19286e-4f + plg[
	    12] * .00216372f + plg[14] * 8.63968e-4f + (plg[10] * .0118068f + 
	    plg[12] * .0033119f) * cd14) * sin(dgtr * *glong));
/*        UT AND MIXED UT,LONGITUDE */
    t12 = (1.f - plg[1] * .565411f) * cos(sr * (*sec - 31137.f)) * (plg[1] * 
	    -.013341f - plg[3] * .0243409f - plg[5] * .0135688f) + (plg[21] * 
	    8.45583e-4f + plg[23] * 5.38706e-4f) * cos(sr * (*sec - 247.956f) 
	    + dgtr * 2.f * *glong);
/*  Exospheric temperature TINF/K  [Eq. A7] */
    *tinf = (t1 + 1.f + t2 + t3 + t5 + t7814 + t11 + t12) * 1041.3f * .99604f;

/* TEMPERATURE DERIVATIVE AT LOWER BOUNDARY */

/*         F10.7 EFFECT */
    t1 = dfa * .00252317f;
/*        TIME INDEPENDENT */
    t2 = plg[2] * -.0467542f + plg[4] * .12026f;
/*        ASYMMETRICAL ANNUAL */
    cd14 = cos(dr * (*iday + 8.45398f));
    t5 = plg[1] * -.13324f * cd14;
/*        SEMIDIURNAL */
    zz = plg[21] * cd14;
    t81 = zz * -.00973404f;
    t82 = zz * -7.18482e-4f;
    t8 = (plg[20] * .0191357f + plg[22] * .00787683f + t81) * c2tloc + (plg[
	    20] * .00125429f - plg[22] * .00233698f + t82) * s2tloc;
/*  dTn/dh at lower boundary  [Eq. A6] */
    g0 = (t1 + 1.f + t2 + t5 + t8) * 16.6728f * .951363f;

/* NEUTRAL TEMPERATURE AT LOWER BOUNDARY 120KM */

    cd9 = cos(dr2 * (*iday - 89.382f));
    cd11 = cos(dr * (*iday + 8.45398f));
    t1 = dfa * 5.68478e-4f;
    t4 = cd9 * .0107674f;
    t5 = plg[1] * -.0192414f * cd11;
    t7 = plg[10] * -.02002f * ctloc - plg[10] * .00195833f * stloc;
    t8 = (plg[20] * -.00938391f - plg[22] * .00260147f + plg[23] * 
	    5.11651e-5f * cd11) * c2tloc + (plg[20] * .013148f - plg[22] * 
	    8.08556e-4f + plg[23] * .00255717f * cd11) * s2tloc;
/*  Tn at lower boundary 120km   [Eq. A8] */
    *tlb = (t1 + 1.f + t4 + t5 + t7 + t8) * 386.f * .976619f;
/*  Sigma      [Eq. A5] */
    *sigma = g0 / (*tinf - *tlb);
    return 0;
} /* cira86_ */



doublereal tn_(real *h__, real *tinf, real *tlbd, real *s)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real zg2;

/* -------------------------------------------------------------------- */
/*       Calculate Temperature for MSIS/CIRA-86 model */
/* -------------------------------------------------------------------- */
    zg2 = (*h__ - 120.f) * 6476.77f / (*h__ + 6356.77f);
    ret_val = *tinf - *tlbd * exp(-(*s) * zg2);
    return ret_val;
} /* tn_ */



doublereal dtndh_(real *h__, real *tinf, real *tlbd, real *s)
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real zg1, zg2, zg3;

/* --------------------------------------------------------------------- */
    zg1 = *h__ + 6356.77f;
    zg2 = 6476.77f / zg1;
    zg3 = (*h__ - 120.f) * zg2;
    ret_val = -(*tlbd) * exp(-(*s) * zg3) * (*s / zg1 * (zg3 - zg2));
    return ret_val;
} /* dtndh_ */

