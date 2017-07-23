#ifndef _CUST_BATTERY_METER_TABLE_H
#define _CUST_BATTERY_METER_TABLE_H

#include <mach/mt_typedefs.h>

// ============================================================
// define
// ============================================================
#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900	
#define RBAT_PULL_DOWN_R		   30000 //27000	//LINE<><20140111><change to 30K >wangyanhui
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900	
#define RBAT_PULL_DOWN_R		  100000	
#endif
#define RBAT_PULL_UP_VOLT          1800



// ============================================================
// ENUM
// ============================================================

// ============================================================
// structure
// ============================================================

// ============================================================
// typedef
// ============================================================
typedef struct _BATTERY_PROFILE_STRUC
{
    kal_int32 percentage;
    kal_int32 voltage;
} BATTERY_PROFILE_STRUC, *BATTERY_PROFILE_STRUC_P;

typedef struct _R_PROFILE_STRUC
{
    kal_int32 resistance; // Ohm
    kal_int32 voltage;
} R_PROFILE_STRUC, *R_PROFILE_STRUC_P;

typedef enum
{
    T1_0C,
    T2_25C,
    T3_50C
} PROFILE_TEMPERATURE;

// ============================================================
// External Variables
// ============================================================

// ============================================================
// External function
// ============================================================

// ============================================================
// <DOD, Battery_Voltage> Table
// ============================================================
//BEGIN <battary> <DATE20130620> <battary tempreature> zhangxiaofei
#if (BAT_NTC_10 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
    	 {-30,124607},
    	 {-25,94918},
        {-20,68237},
        {-15,53650},
        {-10,42506},
        { -5,33892},
        {  0,27219},
        {  5,22021},
        { 10,17926},
        { 15,14674},
        { 20,12081},
        { 25,10000},
        { 30,8315},
        { 35,6948},
        { 40,5834},
        { 45,4917},
        { 50,4161},
        //{ 55,3367}, // zenghaihui
        { 55,3535},
        { 60,3014},
        { 65,2494},
        { 70,2130},
        { 75,1817},
        { 80,1562}
    };
#endif
//END <battary> <DATE20130620> <battary tempreature> zhangxiaofei
#if (BAT_NTC_47 == 1)
    BATT_TEMPERATURE Batt_Temperature_Table[] = {
        {-20,483954},
        {-15,360850},
        {-10,271697},
        { -5,206463},
        {  0,158214},
        {  5,122259},
        { 10,95227},
        { 15,74730},
        { 20,59065},
        { 25,47000},
        { 30,37643},
        { 35,30334},
        { 40,24591},
        { 45,20048},
        { 50,16433},
        { 55,13539},
        { 60,11210}        
    };
#endif

//BEGIN <battary> <DATE20140102> <battary > lishengli
// T0 -10C
BATTERY_PROFILE_STRUC battery_profile_t0[] =
{
//DOD0  OCV -10
{	0  ,	4183 	},
{	2  ,	4167 	},
{	4  ,	4154 	},
{	6  ,	4137 	},
{	7  ,	4117 	},
{	9  ,	4096 	},
{	11 ,	4078 	},
{	13 ,	4059 	},
{	15 ,	4034 	},
{	17 ,	4003 	},
{	18 ,	3979 	},
{	20 ,	3963 	},
{	22 ,	3950 	},
{	24 ,	3938 	},
{	26 ,	3926 	},
{	28 ,	3913 	},
{	29 ,	3902 	},
{	31 ,	3890 	},
{	33 ,	3878 	},
{	35 ,	3867 	},
{	37 ,	3855 	},
{	39 ,	3845 	},
{	41 ,	3835 	},
{	42 ,	3827 	},
{	44 ,	3819 	},
{	46 ,	3812 	},
{	48 ,	3806 	},
{	50 ,	3801 	},
{	52 ,	3797 	},
{	53 ,	3793 	},
{	55 ,	3790 	},
{	57 ,	3786 	},
{	59 ,	3784 	},
{	61 ,	3782 	},
{	63 ,	3781 	},
{	64 ,	3779 	},
{	66 ,	3777 	},
{	68 ,	3774 	},
{	70 ,	3772 	},
{	72 ,	3768 	},
{	74 ,	3762 	},
{	76 ,	3757 	},
{	77 ,	3750 	},
{	79 ,	3742 	},
{	81 ,	3732 	},
{	83 ,	3722 	},
{	85 ,	3712 	},
{	87 ,	3704 	},
{	88 ,	3693 	},
{	90 ,	3683 	},
{	92 ,	3667 	},
{	94 ,	3642 	},
{	96 ,	3604 	},
{	97 ,	3562 	},
{	98 ,	3541 	},
{	98 ,	3528 	},
{	99 ,	3518 	},
{	99 ,	3511 	},
{	99 ,	3504 	},
{	99 ,	3501 	},
{	99 ,	3497 	},
{	100,	3495 	},
{	100,	3491 	},
{	100,	3490 	},
{	100,	3489 	},
{	100,	3488 	},
{	100,	3486 	},
{	100,	3486 	},
{	100,	3486 	},
{	100,	3485 	},
{	100,	3484 	},
{	100,	3483 	},
{	100,	3483 	},
{	100,	3482 	},
{	100,	3400 	}
};              
                
// T1 0C        
BATTERY_PROFILE_STRUC battery_profile_t1[] =
{
	//DOD0	OCV 0
{	0  ,	4185 	},
{	2  ,	4164 	},
{	3  ,	4132 	},
{	5  ,	4094 	},
{	7  ,	4072 	},
{	8  ,	4053 	},
{	10 ,	4033 	},
{	11 ,	4015 	},
{	13 ,	4002 	},
{	15 ,	3990 	},
{	16 ,	3981 	},
{	18 ,	3972 	},
{	20 ,	3961 	},
{	21 ,	3952 	},
{	23 ,	3943 	},
{	25 ,	3932 	},
{	26 ,	3923 	},
{	28 ,	3913 	},
{	29 ,	3903 	},
{	31 ,	3893 	},
{	33 ,	3883 	},
{	34 ,	3873 	},
{	36 ,	3862 	},
{	38 ,	3852 	},
{	39 ,	3841 	},
{	41 ,	3831 	},
{	43 ,	3823 	},
{	44 ,	3815 	},
{	46 ,	3808 	},
{	47 ,	3802 	},
{	49 ,	3797 	},
{	51 ,	3793 	},
{	52 ,	3789 	},
{	54 ,	3786 	},
{	56 ,	3784 	},
{	57 ,	3782 	},
{	59 ,	3781 	},
{	60 ,	3780 	},
{	62 ,	3780 	},
{	64 ,	3779 	},
{	65 ,	3778 	},
{	67 ,	3777 	},
{	69 ,	3776 	},
{	70 ,	3775 	},
{	72 ,	3773 	},
{	74 ,	3770 	},
{	75 ,	3768 	},
{	77 ,	3763 	},
{	79 ,	3757 	},
{	80 ,	3749 	},
{	82 ,	3740 	},
{	83 ,	3728 	},
{	85 ,	3714 	},
{	87 ,	3699 	},
{	88 ,	3684 	},
{	90 ,	3666 	},
{	92 ,	3643 	},
{	93 ,	3617 	},
{	95 ,	3588 	},
{	96 ,	3563 	},
{	98 ,	3540 	},
{	99 ,	3512 	},
{	100,	3414 	},
{	100,	3395 	},
{	100,	3390 	},
{	100,	3388 	},
{	100,	3385 	},
{	100,	3384 	},
{	100,	3383 	},
{	100,	3382 	},
{	100,	3381 	},
{	100,	3385 	},
{	100,	3385 	},
{	100,	3385 	},
{	100,	3385 	}
};              

// T2 25C
BATTERY_PROFILE_STRUC battery_profile_t2[] =
{
	//DOD0	OCV 25	
{	0  ,	4187 	},
{	2  ,	4170 	},
{	3  ,	4153 	},
{	5  ,	4138 	},
{	6  ,	4122 	},
{	8  ,	4107 	},
{	10 ,	4094 	},
{	11 ,	4080 	},
{	13 ,	4067 	},
{	15 ,	4053 	},
{	16 ,	4039 	},
{	18 ,	4025 	},
{	20 ,	4012 	},
{	21 ,	4000 	},
{	23 ,	3989 	},
{	24 ,	3978 	},
{	26 ,	3967 	},
{	28 ,	3956 	},
{	29 ,	3945 	},
{	31 ,	3934 	},
{	33 ,	3922 	},
{	34 ,	3910 	},
{	36 ,	3898 	},
{	37 ,	3885 	},
{	39 ,	3872 	},
{	41 ,	3860 	},
{	42 ,	3849 	},
{	44 ,	3840 	},
{	46 ,	3832 	},
{	47 ,	3825 	},
{	49 ,	3818 	},
{	51 ,	3811 	},
{	52 ,	3806 	},
{	54 ,	3801 	},
{	55 ,	3796 	},
{	57 ,	3792 	},
{	59 ,	3788 	},
{	60 ,	3784 	},
{	62 ,	3780 	},
{	64 ,	3777 	},
{	65 ,	3775 	},
{	67 ,	3772 	},
{	68 ,	3771 	},
{	70 ,	3768 	},
{	72 ,	3766 	},
{	73 ,	3761 	},
{	75 ,	3756 	},
{	77 ,	3749 	},
{	78 ,	3743 	},
{	80 ,	3738 	},
{	81 ,	3732 	},
{	83 ,	3722 	},
{	85 ,	3711 	},
{	86 ,	3699 	},
{	88 ,	3688 	},
{	90 ,	3684 	},
{	91 ,	3677 	},
{	93 ,	3666 	},
{	95 ,	3651 	},
{	96 ,	3623 	},
{	98 ,	3562 	},
{	99 ,	3460 	},
{	100,	3293 	},
{	100,	3269 	},
{	100,	3261 	},
{	100,	3257 	},
{	100,	3256 	},
{	100,	3255 	},
{	100,	3254 	},
{	100,	3253 	},
{	100,	3252 	},
{	100,	3251 	},
{	100,	3253 	},
{	100,	3253 	},
{	100,	3254 	}
};              

// T3 50C
BATTERY_PROFILE_STRUC battery_profile_t3[] =
{
	//DOD0	OCV 50	
{	0  ,	4193 	},
{	2  ,	4177 	},
{	3  ,	4161 	},
{	5  ,	4145 	},
{	6  ,	4130 	},
{	8  ,	4115 	},
{	10 ,	4100 	},
{	11 ,	4086 	},
{	13 ,	4072 	},
{	14 ,	4059 	},
{	16 ,	4045 	},
{	18 ,	4032 	},
{	19 ,	4020 	},
{	21 ,	4007 	},
{	22 ,	3995 	},
{	24 ,	3984 	},
{	26 ,	3972 	},
{	27 ,	3962 	},
{	29 ,	3950 	},
{	30 ,	3939 	},
{	32 ,	3929 	},
{	34 ,	3919 	},
{	35 ,	3908 	},
{	37 ,	3897 	},
{	38 ,	3885 	},
{	40 ,	3871 	},
{	42 ,	3858 	},
{	43 ,	3847 	},
{	45 ,	3838 	},
{	46 ,	3829 	},
{	48 ,	3822 	},
{	50 ,	3816 	},
{	51 ,	3809 	},
{	53 ,	3803 	},
{	54 ,	3798 	},
{	56 ,	3792 	},
{	58 ,	3788 	},
{	59 ,	3784 	},
{	61 ,	3779 	},
{	62 ,	3776 	},
{	64 ,	3772 	},
{	66 ,	3769 	},
{	67 ,	3766 	},
{	69 ,	3762 	},
{	70 ,	3755 	},
{	72 ,	3747 	},
{	74 ,	3743 	},
{	75 ,	3737 	},
{	77 ,	3731 	},
{	78 ,	3725 	},
{	80 ,	3720 	},
{	82 ,	3714 	},
{	83 ,	3704 	},
{	85 ,	3695 	},
{	86 ,	3684 	},
{	88 ,	3672 	},
{	90 ,	3668 	},
{	91 ,	3663 	},
{	93 ,	3653 	},
{	94 ,	3641 	},
{	96 ,	3617 	},
{	98 ,	3560 	},
{	99 ,	3466 	},
{	100,	3318 	},
{	100,	3257 	},
{	100,	3251 	},
{	100,	3247 	},
{	100,	3247 	},
{	100,	3245 	},
{	100,	3245 	},
{	100,	3244 	},
{	100,	3244 	},
{	100,	3243 	},
{	100,	3243 	},
{	100,	3243 	}
};              

// battery profile for actual temperature. The size should be the same as T1, T2 and T3
BATTERY_PROFILE_STRUC battery_profile_temperature[] =
{
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	}
};           
 
// ============================================================
// <Rbat, Battery_Voltage> Table
// ============================================================
// T0 -10C
R_PROFILE_STRUC r_profile_t0[] =
{
	//DOD0	R -10
{	268,	4183 	},
{	263,	4167 	},
{	270,	4154 	},
{	275,	4137 	},
{	283,	4117 	},
{	285,	4096 	},
{	295,	4078 	},
{	310,	4059 	},
{	358,	4034 	},
{	445,	4003 	},
{	525,	3979 	},
{	603,	3963 	},
{	623,	3950 	},
{	635,	3938 	},
{	640,	3926 	},
{	643,	3913 	},
{	648,	3902 	},
{	648,	3890 	},
{	645,	3878 	},
{	648,	3867 	},
{	643,	3855 	},
{	643,	3845 	},
{	640,	3835 	},
{	643,	3827 	},
{	640,	3819 	},
{	643,	3812 	},
{	645,	3806 	},
{	650,	3801 	},
{	658,	3797 	},
{	660,	3793 	},
{	665,	3790 	},
{	665,	3786 	},
{	670,	3784 	},
{	675,	3782 	},
{	678,	3781 	},
{	683,	3779 	},
{	688,	3777 	},
{	690,	3774 	},
{	695,	3772 	},
{	693,	3768 	},
{	693,	3762 	},
{	695,	3757 	},
{	698,	3750 	},
{	698,	3742 	},
{	698,	3732 	},
{	700,	3722 	},
{	710,	3712 	},
{	730,	3704 	},
{	755,	3693 	},
{	790,	3683 	},
{	825,	3667 	},
{	860,	3642 	},
{	893,	3604 	},
{	908,	3562 	},
{	853,	3541 	},
{	820,	3528 	},
{	798,	3518 	},
{	780,	3511 	},
{	763,	3504 	},
{	753,	3501 	},
{	748,	3497 	},
{	743,	3495 	},
{	733,	3491 	},
{	725,	3490 	},
{	728,	3489 	},
{	728,	3488 	},
{	715,	3486 	},
{	715,	3486 	},
{	715,	3486 	},
{	718,	3485 	},
{	718,	3484 	},
{	718,	3483 	},
{	718,	3483 	},
{	715,	3482 	},
{	510,	3400 	}
};           

// T1 0C
R_PROFILE_STRUC r_profile_t1[] =
{
	//DOD0	R 0
{	225,	4185 	},
{	213,	4164 	},
{	215,	4132 	},
{	265,	4094 	},
{	318,	4072 	},
{	340,	4053 	},
{	348,	4033 	},
{	355,	4015 	},
{	365,	4002 	},
{	368,	3990 	},
{	375,	3981 	},
{	380,	3972 	},
{	383,	3961 	},
{	390,	3952 	},
{	393,	3943 	},
{	395,	3932 	},
{	400,	3923 	},
{	400,	3913 	},
{	403,	3903 	},
{	400,	3893 	},
{	400,	3883 	},
{	400,	3873 	},
{	393,	3862 	},
{	385,	3852 	},
{	378,	3841 	},
{	373,	3831 	},
{	370,	3823 	},
{	370,	3815 	},
{	368,	3808 	},
{	368,	3802 	},
{	370,	3797 	},
{	368,	3793 	},
{	370,	3789 	},
{	373,	3786 	},
{	378,	3784 	},
{	380,	3782 	},
{	383,	3781 	},
{	388,	3780 	},
{	390,	3780 	},
{	390,	3779 	},
{	393,	3778 	},
{	393,	3777 	},
{	398,	3776 	},
{	400,	3775 	},
{	403,	3773 	},
{	403,	3770 	},
{	408,	3768 	},
{	408,	3763 	},
{	410,	3757 	},
{	415,	3749 	},
{	423,	3740 	},
{	428,	3728 	},
{	435,	3714 	},
{	445,	3699 	},
{	455,	3684 	},
{	463,	3666 	},
{	465,	3643 	},
{	468,	3617 	},
{	470,	3588 	},
{	488,	3563 	},
{	515,	3540 	},
{	558,	3512 	},
{	488,	3414 	},
{	488,	3395 	},
{	475,	3390 	},
{	473,	3388 	},
{	468,	3385 	},
{	460,	3384 	},
{	465,	3383 	},
{	455,	3382 	},
{	458,	3381 	},
{	465,	3385 	},
{	468,	3385 	},
{	470,	3385 	},
{	468,	3385 	}
};           

// T2 25C
R_PROFILE_STRUC r_profile_t2[] =
{
	//DOD0	R 25
	
{	138,	4187 	},
{	158,	4170 	},
{	158,	4153 	},
{	158,	4138 	},
{	158,	4122 	},
{	158,	4107 	},
{	163,	4094 	},
{	163,	4080 	},
{	165,	4067 	},
{	165,	4053 	},
{	168,	4039 	},
{	170,	4025 	},
{	168,	4012 	},
{	175,	4000 	},
{	180,	3989 	},
{	180,	3978 	},
{	183,	3967 	},
{	188,	3956 	},
{	190,	3945 	},
{	193,	3934 	},
{	193,	3922 	},
{	193,	3910 	},
{	188,	3898 	},
{	183,	3885 	},
{	175,	3872 	},
{	168,	3860 	},
{	163,	3849 	},
{	163,	3840 	},
{	160,	3832 	},
{	158,	3825 	},
{	158,	3818 	},
{	155,	3811 	},
{	160,	3806 	},
{	160,	3801 	},
{	160,	3796 	},
{	160,	3792 	},
{	165,	3788 	},
{	163,	3784 	},
{	163,	3780 	},
{	163,	3777 	},
{	168,	3775 	},
{	163,	3772 	},
{	168,	3771 	},
{	165,	3768 	},
{	165,	3766 	},
{	163,	3761 	},
{	160,	3756 	},
{	158,	3749 	},
{	158,	3743 	},
{	160,	3738 	},
{	168,	3732 	},
{	165,	3722 	},
{	163,	3711 	},
{	163,	3699 	},
{	163,	3688 	},
{	168,	3684 	},
{	170,	3677 	},
{	178,	3666 	},
{	200,	3651 	},
{	215,	3623 	},
{	205,	3562 	},
{	205,	3460 	},
{	220,	3293 	},
{	175,	3269 	},
{	158,	3261 	},
{	145,	3257 	},
{	143,	3256 	},
{	143,	3255 	},
{	143,	3254 	},
{	138,	3253 	},
{	140,	3252 	},
{	130,	3251 	},
{	138,	3253 	},
{	135,	3253 	},
{	148,	3254 	}
};           

// T3 50C
R_PROFILE_STRUC r_profile_t3[] =
{
	//DOD0	R 50
{	110,	4193 	},
{	118,	4177 	},
{	120,	4161 	},
{	120,	4145 	},
{	123,	4130 	},
{	120,	4115 	},
{	120,	4100 	},
{	120,	4086 	},
{	123,	4072 	},
{	125,	4059 	},
{	125,	4045 	},
{	125,	4032 	},
{	128,	4020 	},
{	125,	4007 	},
{	128,	3995 	},
{	130,	3984 	},
{	133,	3972 	},
{	135,	3962 	},
{	135,	3950 	},
{	138,	3939 	},
{	140,	3929 	},
{	145,	3919 	},
{	145,	3908 	},
{	145,	3897 	},
{	145,	3885 	},
{	138,	3871 	},
{	130,	3858 	},
{	128,	3847 	},
{	125,	3838 	},
{	123,	3829 	},
{	123,	3822 	},
{	125,	3816 	},
{	123,	3809 	},
{	123,	3803 	},
{	125,	3798 	},
{	125,	3792 	},
{	128,	3788 	},
{	128,	3784 	},
{	128,	3779 	},
{	130,	3776 	},
{	130,	3772 	},
{	130,	3769 	},
{	133,	3766 	},
{	133,	3762 	},
{	123,	3755 	},
{	123,	3747 	},
{	125,	3743 	},
{	123,	3737 	},
{	123,	3731 	},
{	120,	3725 	},
{	123,	3720 	},
{	123,	3714 	},
{	120,	3704 	},
{	123,	3695 	},
{	125,	3684 	},
{	125,	3672 	},
{	128,	3668 	},
{	133,	3663 	},
{	130,	3653 	},
{	140,	3641 	},
{	145,	3617 	},
{	143,	3560 	},
{	145,	3466 	},
{	150,	3318 	},
{	145,	3257 	},
{	128,	3251 	},
{	123,	3247 	},
{	118,	3247 	},
{	118,	3245 	},
{	113,	3245 	},
{	113,	3244 	},
{	115,	3244 	},
{	115,	3243 	},
{	113,	3243 	},
{	113,	3243 	}
};           

// r-table profile for actual temperature. The size should be the same as T1, T2 and T3
R_PROFILE_STRUC r_profile_temperature[] =
{
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	},
{	0,	0 	}
};           
//END <battary> <DATE20140102> <battary > lishengli

// ============================================================
// function prototype
// ============================================================
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUC_P fgauge_get_profile(kal_uint32 temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUC_P fgauge_get_profile_r_table(kal_uint32 temperature);

#endif	//#ifndef _CUST_BATTERY_METER_TABLE_H

