<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * SDIF includes.  These includes define information used in 
 * the SDIF classes and child classes in the Flip-Turn web application.
 *
 * This information is based on the United States Swimming Interchange
 * format version 3 document revision F.  This document can be found on
 * the US Swimming web site at:  http://www.usaswimming.org/
 *
 * This file is derived from the file of the same name found at:
 * https://wp-swimteam.svn.sourceforge.net/svnroot/wp-swimteam/plugin/trunk/include/sdif.include.php
 *
 * (c) 2007 by Mike Walsh for Wp-SwimTeam.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package Flip-Turn
 * @subpackage SDIF
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 *
 */

define('FT_SDIF_VERSION', '3.0') ;
define('FT_SDIF_FUTURE_USE', '') ;
define('FT_SDIF_NO_VALUE', '') ;
define('FT_SDIF_SOFTWARE_NAME', 'Flip-Turn') ;
define('FT_SDIF_SOFTWARE_VERSION', 'v0.1') ;

/**
 *  Organization Code
 *
 *  ORG Code 001      Organization code
 *       1    USS                        6    NCAA Div III
 *       2    Masters                    7    YMCA
 *       3    NCAA                       8    FINA
 *       4    NCAA Div I                 9    High School
 *       5    NCAA Div II
 */

//  Define the labels used in the GUI
define("FT_SDIF_ORG_CODE_USS_LABEL", "USS") ;
define("FT_SDIF_ORG_CODE_MASTERS_LABEL", "Masters") ;
define("FT_SDIF_ORG_CODE_NCAA_LABEL", "NCAA") ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_I_LABEL", "NCAA Div I") ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_II_LABEL", "NCAA Div II") ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_III_LABEL", "NCAA Div III") ;
define("FT_SDIF_ORG_CODE_YMCA_LABEL", "YMCA") ;
define("FT_SDIF_ORG_CODE_FINA_LABEL", "FINA") ;
define("FT_SDIF_ORG_CODE_HIGH_SCHOOL_LABEL", "High School") ;

//  Define the values used in the records
define("FT_SDIF_ORG_CODE_USS_VALUE", 1) ;
define("FT_SDIF_ORG_CODE_MASTERS_VALUE", 2) ;
define("FT_SDIF_ORG_CODE_NCAA_VALUE", 3) ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_I_VALUE", 4) ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_II_VALUE", 5) ;
define("FT_SDIF_ORG_CODE_NCAA_DIV_III_VALUE", 6) ;
define("FT_SDIF_ORG_CODE_YMCA_VALUE", 7) ;
define("FT_SDIF_ORG_CODE_FINA_VALUE", 8) ;
define("FT_SDIF_ORG_CODE_HIGH_SCHOOL_VALUE", 9) ;

/**
 *  Local Swimming Committee Code
 *
 *  LSC Code 002      Local Swimming Committee code
 *       AD   Adirondack                 MV    Missouri Valley
 *       AK   Alaska                     MW    Midwestern
 *       AM   Allegheny Mountain         NC    North Carolina
 *       AR   Arkansas                   ND    North Dakota
 *       AZ   Arizona                    NE    New England
 *       BD   Border                     NI    Niagara
 *       CA   Southern California        NJ    New Jersey
 *       CC   Central California         NM    New Mexico
 *       CO   Colorado                   NT    North Texas
 *       CT   Connecticut                OH    Ohio
 *       FG   Florida Gold Coast         OK    Oklahoma
 *       FL   Florida                    OR    Oregon
 *       GA   Georgia                    OZ    Ozark
 *       GU   Gulf                       PC    Pacific
 *       HI   Hawaii                     PN    Pacific Northwest
 *       IA   Iowa                       PV    Potomac Valley
 *       IE   Inland Empire              SC    South Carolina
 *       IL   Illinois                   SD    South Dakota
 *       IN   Indiana                    SE    Southeastern
 *       KY   Kentucky                   SI    San Diego Imperial
 *       LA   Louisiana                  SN    Sierra Nevada
 *       LE   Lake Erie                  SR    Snake River
 *       MA   Middle Atlantic            ST    South Texas
 *       MD   Maryland                   UT    Utah
 *       ME   Maine                      VA    Virginia
 *       MI   Michigan                   WI    Wisconsin
 *       MN   Minnesota                  WT    West Texas
 *       MR   Metropolitan               WV    West Virginia
 *       MS   Mississippi                WY    Wyoming
 *       MT   Montana
 */

//  Define the labels used in the GUI
define("FT_SDIF_LSC_CODE_ADIRONDACK_LABEL", "Adirondack") ;
define("FT_SDIF_LSC_CODE_ALASKA_LABEL", "Alaska") ;
define("FT_SDIF_LSC_CODE_ALLEGHENY_MOUNTAIN_LABEL", "Allegheny Mountain") ;
define("FT_SDIF_LSC_CODE_ARKANSAS_LABEL", "Arkansas") ;
define("FT_SDIF_LSC_CODE_ARIZONA_LABEL", "Arizona") ;
define("FT_SDIF_LSC_CODE_BORDER_LABEL", "Border") ;
define("FT_SDIF_LSC_CODE_CENTRAL_CALIFORNIA_LABEL", "Central California") ;
define("FT_SDIF_LSC_CODE_COLORADO_LABEL", "Colorado") ;
define("FT_SDIF_LSC_CODE_CONNECTICUT_LABEL", "Connecticut") ;
define("FT_SDIF_LSC_CODE_FLORIDA_GOLD_COAST_LABEL", "Florida Gold Coast") ;
define("FT_SDIF_LSC_CODE_FLORIDA_LABEL", "Florida") ;
define("FT_SDIF_LSC_CODE_GEORGIA_LABEL", "Georgia") ;
define("FT_SDIF_LSC_CODE_GULF_LABEL", "Gulf") ;
define("FT_SDIF_LSC_CODE_HAWAII_LABEL", "Hawaii") ;
define("FT_SDIF_LSC_CODE_IOWA_LABEL", "Iowa") ;
define("FT_SDIF_LSC_CODE_INLAND_EMPIRE_LABEL", "Inland Empire") ;
define("FT_SDIF_LSC_CODE_ILLINOIS_LABEL", "Illinois") ;
define("FT_SDIF_LSC_CODE_INDIANA_LABEL", "Indiana") ;
define("FT_SDIF_LSC_CODE_KENTUCKY_LABEL", "Kentucky") ;
define("FT_SDIF_LSC_CODE_LOUISIANA_LABEL", "Louisiana") ;
define("FT_SDIF_LSC_CODE_LAKE_ERIE_LABEL", "Lake Erie") ;
define("FT_SDIF_LSC_CODE_MIDDLE_ATLANTIC_LABEL", "Middle Atlantic") ;
define("FT_SDIF_LSC_CODE_MARYLAND_LABEL", "Maryland") ;
define("FT_SDIF_LSC_CODE_MAINE_LABEL", "Maine") ;
define("FT_SDIF_LSC_CODE_MINNESOTA_LABEL", "Minnesota") ;
define("FT_SDIF_LSC_CODE_MICHIGAN_LABEL", "Michigan") ;
define("FT_SDIF_LSC_CODE_METROPOLITAN_LABEL", "Metropolitan") ;
define("FT_SDIF_LSC_CODE_MISSISSIPPI_LABEL", "Mississippi") ;
define("FT_SDIF_LSC_CODE_MONTANA_LABEL", "Montana") ;
define("FT_SDIF_LSC_CODE_MISSOURI_VALLEY_LABEL", "Missouri Valley") ;
define("FT_SDIF_LSC_CODE_MIDWESTERN_LABEL", "Midwestern") ;
define("FT_SDIF_LSC_CODE_NORTH_CAROLINA_LABEL", "North Carolina") ;
define("FT_SDIF_LSC_CODE_NORTH_DAKOTA_LABEL", "North Dakota") ;
define("FT_SDIF_LSC_CODE_NEW_ENGLAND_LABEL", "New England") ;
define("FT_SDIF_LSC_CODE_NIAGARA_LABEL", "Niagara") ;
define("FT_SDIF_LSC_CODE_NEW_JERSEY_LABEL", "New Jersey") ;
define("FT_SDIF_LSC_CODE_NEW_MEXICO_LABEL", "New Mexico") ;
define("FT_SDIF_LSC_CODE_NORTH_TEXAS_LABEL", "North Texas") ;
define("FT_SDIF_LSC_CODE_OHIO_LABEL", "Ohio") ;
define("FT_SDIF_LSC_CODE_OKLAHOMA_LABEL", "Oklahoma") ;
define("FT_SDIF_LSC_CODE_OREGON_LABEL", "Oregon") ;
define("FT_SDIF_LSC_CODE_OZARK_LABEL", "Ozark") ;
define("FT_SDIF_LSC_CODE_PACIFIC_LABEL", "Pacific") ;
define("FT_SDIF_LSC_CODE_PACIFIC_NORTHWEST_LABEL", "Pacific Northwest") ;
define("FT_SDIF_LSC_CODE_POTOMAC_VALLEY_LABEL", "Potomac Valley") ;
define("FT_SDIF_LSC_CODE_SOUTH_CAROLINA_LABEL", "South Carolina") ;
define("FT_SDIF_LSC_CODE_SOUTH_DAKOTA_LABEL", "South Dakota") ;
define("FT_SDIF_LSC_CODE_SOUTHEASTERN_LABEL", "Southeastern") ;
define("FT_SDIF_LSC_CODE_SOUTHERN_CALIFORNIA_LABEL", "Southern California") ;
define("FT_SDIF_LSC_CODE_SAN_DIEGO_IMPERIAL_LABEL", "San Diego Imperial") ;
define("FT_SDIF_LSC_CODE_WEST_TEXAS_LABEL", "West Texas") ;
define("FT_SDIF_LSC_CODE_SIERRA_NEVADA_LABEL", "Sierra Nevada") ;
define("FT_SDIF_LSC_CODE_SNAKE_RIVER_LABEL", "Snake River") ;
define("FT_SDIF_LSC_CODE_SOUTH_TEXAS_LABEL", "South Texas") ;
define("FT_SDIF_LSC_CODE_UTAH_LABEL", "Utah") ;
define("FT_SDIF_LSC_CODE_VIRGINIA_LABEL", "Virginia") ;
define("FT_SDIF_LSC_CODE_WISCONSIN_LABEL", "Wisconsin") ;
define("FT_SDIF_LSC_CODE_WEST_VIRGINIA_LABEL", "West Virginia") ;
define("FT_SDIF_LSC_CODE_WYOMING_LABEL", "Wyoming") ;

//  Define the values used in the records
define("FT_SDIF_LSC_CODE_ADIRONDACK_VALUE", "AD") ;
define("FT_SDIF_LSC_CODE_ALASKA_VALUE", "AK") ;
define("FT_SDIF_LSC_CODE_ALLEGHENY_MOUNTAIN_VALUE", "AM") ;
define("FT_SDIF_LSC_CODE_ARKANSAS_VALUE", "AR") ;
define("FT_SDIF_LSC_CODE_ARIZONA_VALUE", "AZ") ;
define("FT_SDIF_LSC_CODE_BORDER_VALUE", "BD") ;
define("FT_SDIF_LSC_CODE_CENTRAL_CALIFORNIA_VALUE", "CC") ;
define("FT_SDIF_LSC_CODE_COLORADO_VALUE", "CO") ;
define("FT_SDIF_LSC_CODE_CONNECTICUT_VALUE", "CT") ;
define("FT_SDIF_LSC_CODE_FLORIDA_GOLD_COAST_VALUE", "FG") ;
define("FT_SDIF_LSC_CODE_FLORIDA_VALUE", "FL") ;
define("FT_SDIF_LSC_CODE_GEORGIA_VALUE", "GA") ;
define("FT_SDIF_LSC_CODE_GULF_VALUE", "GU") ;
define("FT_SDIF_LSC_CODE_HAWAII_VALUE", "HI") ;
define("FT_SDIF_LSC_CODE_IOWA_VALUE", "IA") ;
define("FT_SDIF_LSC_CODE_INLAND_EMPIRE_VALUE", "IE") ;
define("FT_SDIF_LSC_CODE_ILLINOIS_VALUE", "IL") ;
define("FT_SDIF_LSC_CODE_INDIANA_VALUE", "IN") ;
define("FT_SDIF_LSC_CODE_KENTUCKY_VALUE", "KY") ;
define("FT_SDIF_LSC_CODE_LOUISIANA_VALUE", "LA") ;
define("FT_SDIF_LSC_CODE_LAKE_ERIE_VALUE", "LE") ;
define("FT_SDIF_LSC_CODE_MIDDLE_ATLANTIC_VALUE", "MA") ;
define("FT_SDIF_LSC_CODE_MARYLAND_VALUE", "MD") ;
define("FT_SDIF_LSC_CODE_MAINE_VALUE", "ME") ;
define("FT_SDIF_LSC_CODE_MINNESOTA_VALUE", "MN") ;
define("FT_SDIF_LSC_CODE_MICHIGAN_VALUE", "MI") ;
define("FT_SDIF_LSC_CODE_METROPOLITAN_VALUE", "MR") ;
define("FT_SDIF_LSC_CODE_MISSISSIPPI_VALUE", "MS") ;
define("FT_SDIF_LSC_CODE_MONTANA_VALUE", "MT") ;
define("FT_SDIF_LSC_CODE_MISSOURI_VALLEY_VALUE", "MV") ;
define("FT_SDIF_LSC_CODE_MIDWESTERN_VALUE", "MW") ;
define("FT_SDIF_LSC_CODE_NORTH_CAROLINA_VALUE", "NC") ;
define("FT_SDIF_LSC_CODE_NORTH_DAKOTA_VALUE", "ND") ;
define("FT_SDIF_LSC_CODE_NEW_ENGLAND_VALUE", "NE") ;
define("FT_SDIF_LSC_CODE_NIAGARA_VALUE", "NI") ;
define("FT_SDIF_LSC_CODE_NEW_JERSEY_VALUE", "NJ") ;
define("FT_SDIF_LSC_CODE_NEW_MEXICO_VALUE", "NM") ;
define("FT_SDIF_LSC_CODE_NORTH_TEXAS_VALUE", "NT") ;
define("FT_SDIF_LSC_CODE_OHIO_VALUE", "OH") ;
define("FT_SDIF_LSC_CODE_OKLAHOMA_VALUE", "OK") ;
define("FT_SDIF_LSC_CODE_OREGON_VALUE", "OR") ;
define("FT_SDIF_LSC_CODE_OZARK_VALUE", "OZ") ;
define("FT_SDIF_LSC_CODE_PACIFIC_VALUE", "PC") ;
define("FT_SDIF_LSC_CODE_PACIFIC_NORTHWEST_VALUE", "PN") ;
define("FT_SDIF_LSC_CODE_POTOMAC_VALLEY_VALUE", "PV") ;
define("FT_SDIF_LSC_CODE_SOUTH_CAROLINA_VALUE", "SC") ;
define("FT_SDIF_LSC_CODE_SOUTH_DAKOTA_VALUE", "SD") ;
define("FT_SDIF_LSC_CODE_SOUTHEASTERN_VALUE", "SE") ;
define("FT_SDIF_LSC_CODE_SOUTHERN_CALIFORNIA_VALUE", "CA") ;
define("FT_SDIF_LSC_CODE_SAN_DIEGO_IMPERIAL_VALUE", "SI") ;
define("FT_SDIF_LSC_CODE_SIERRA_NEVADA_VALUE", "SN") ;
define("FT_SDIF_LSC_CODE_SNAKE_RIVER_VALUE", "SR") ;
define("FT_SDIF_LSC_CODE_SOUTH_TEXAS_VALUE", "ST") ;
define("FT_SDIF_LSC_CODE_UTAH_VALUE", "UT") ;
define("FT_SDIF_LSC_CODE_VIRGINIA_VALUE", "VA") ;
define("FT_SDIF_LSC_CODE_WISCONSIN_VALUE", "WI") ;
define("FT_SDIF_LSC_CODE_WEST_TEXAS_VALUE", "WT") ;
define("FT_SDIF_LSC_CODE_WEST_VIRGINIA_VALUE", "WV") ;
define("FT_SDIF_LSC_CODE_WYOMING_VALUE", "WY") ;
 

/**
 *  File/Transmission Type Code
 *
 *  FILE Code 003     File/Transmission Type code
 *       01   Meet Registrations
 *       02   Meet Results
 *       03   OVC
 *       04   National Age Group Record
 *       05   LSC Age Group Record
 *       06   LSC Motivational List
 *       07   National Records and Rankings
 *       08   Team Selection
 *       09   LSC Best Times
 *       10   USS Registration
 *       16   Top 16
 *       20   Vendor-defined code
 */

//  Define the labels used in the GUI
define("FT_SDIF_FTT_CODE_MEET_REGISTRATIONS_LABEL", "Meet Registrations") ;
define("FT_SDIF_FTT_CODE_MEET_RESULTS_LABEL", "Meet Results") ;
define("FT_SDIF_FTT_CODE_OVC_LABEL", "OVC") ;
define("FT_SDIF_FTT_CODE_NATIONAL_AGE_GROUP_RECORD_LABEL", "National Age Group Record") ;
define("FT_SDIF_FTT_CODE_LSC_AGE_GROUP_RECORD_LABEL", "LSC Age Group Record") ;
define("FT_SDIF_FTT_CODE_LSC_MOTIVATIONAL_LIST_LABEL", "LSC Motivational List") ;
define("FT_SDIF_FTT_CODE_NATIONAL_RECORDS_AND_RANKINGS_LABEL", "National Records and Rankings") ;
define("FT_SDIF_FTT_CODE_TEAM_SELECTION_LABEL", "Team Selection") ;
define("FT_SDIF_FTT_CODE_LSC_BEST_TIMES_LABEL", "LSC Best Times") ;
define("FT_SDIF_FTT_CODE_USS_REGISTRATION_LABEL", "USS Registration") ;
define("FT_SDIF_FTT_CODE_TOP_LABEL", "Top") ;
define("FT_SDIF_FTT_CODE_VENDOR_DEFINED_CODE_LABEL", "Vendor-defined code") ;

//  Define the values used in the records
DEFINE("FT_SDIF_FTT_CODE_MEET_REGISTRATIONS_VALUE", "01") ;
DEFINE("FT_SDIF_FTT_CODE_MEET_RESULTS_VALUE", "02") ;
DEFINE("FT_SDIF_FTT_CODE_OVC_VALUE", "03") ;
DEFINE("FT_SDIF_FTT_CODE_NATIONAL_AGE_GROUP_RECORD_VALUE", "04") ;
DEFINE("FT_SDIF_FTT_CODE_LSC_AGE_GROUP_RECORD_VALUE", "05") ;
DEFINE("FT_SDIF_FTT_CODE_LSC_MOTIVATIONAL_LIST_VALUE", "06") ;
DEFINE("FT_SDIF_FTT_CODE_NATIONAL_RECORDS_AND_RANKINGS_VALUE", "07") ;
DEFINE("FT_SDIF_FTT_CODE_TEAM_SELECTION_VALUE", "08") ;
DEFINE("FT_SDIF_FTT_CODE_LSC_BEST_TIMES_VALUE", "09") ;
DEFINE("FT_SDIF_FTT_CODE_USS_REGISTRATION_VALUE", "10") ;
DEFINE("FT_SDIF_FTT_CODE_TOP_VALUE", "16") ;
DEFINE("FT_SDIF_FTT_CODE_VENDOR_DEFINED_CODE_VALUE", "20") ;

/**
 * FINA Country code (effective 1993)
 *
 * COUNTRY Code 004    FINA Country code (effective 1993)
 *
 *      AFG  Afghanistan                BRN   Bahrain    
 *      AHO  Antilles Netherlands       BRU   Brunei   
 *           (Dutch West Indies)        BUL   Bulgaria    
 *      ALB  Albania                    BUR   Burkina Faso
 *      ALG  Algeria                    CAF   Central African
 *      AND  Andorra                          Republic
 *      ANG  Angola                     CAN   Canada
 *      ANT  Antigua                    CAY   Cayman Islands
 *      ARG  Argentina                  CGO   People's Rep. of Congo
 *      ARM  Armenia                    CHA   Chad    
 *      ARU  Aruba                      CHI   Chile              
 *      ASA  American Samoa             CHN   People's Rep. of China
 *      AUS  Australia                  CIV   Ivory Coast           
 *      AUT  Austria                    CMR   Cameroon    
 *      AZE  Azerbaijan                 COK   Cook Islands
 *      BAH  Bahamas                    COL   Columbia
 *      BAN  Bangladesh                 CRC   Costa Rica
 *      BAR  Barbados                   CRO   Croatia
 *      BEL  Belgium                    CUB   Cuba    
 *      BEN  Benin                      CYP   Cyprus
 *      BER  Bermuda                    DEN   Denmark
 *      BHU  Bhutan                     DJI   Djibouti
 *      BIZ  Belize                     DOM   Dominican Republic
 *      BLS  Belarus                    ECU   Ecuador
 *      BOL  Bolivia                    EGY   Arab Republic of Egypt
 *      BOT  Botswana                   ESA   El Salvador      
 *      BRA  Brazil                     ESP   Spain
 *      EST   Estonia                   LAO   Laos
 *      ETH   Ethiopia                  LAT   Latvia
 *      FIJ   Fiji                      LBA   Libya
 *      FIN   Finland                   LBR   Liberia
 *      FRA   France                    LES   Lesotho
 *      GAB   Gabon                     LIB   Lebanon
 *      GAM   Gambia                    LIE   Liechtenstein
 *      GBR   Great Britain             LIT   Lithuania
 *      GER   Germany                   LUX   Luxembourg
 *      GEO   Georgia                   MAD   Madagascar
 *      GEQ   Equatorial Guinea         MAS   Malaysia
 *      GHA   Ghana                     MAR   Morocco
 *      GRE   Greece                    MAW   Malawi
 *      GRN   Grenada                   MDV   Maldives
 *      GUA   Guatemala                 MEX   Mexico
 *      GUI   Guinea                    MGL   Mongolia
 *      GUM   Guam                      MLD   Moldova
 *      GUY   Guyana                    MLI   Mali
 *      HAI   Haiti                     MLT   Malta
 *      HKG   Hong Kong                 MON   Monaco
 *      HON   Honduras                  MOZ   Mozambique
 *      HUN   Hungary                   MRI   Mauritius
 *      INA   Indonesia                 MTN   Mauritania
 *      IND   India                     MYA   Union of Myanmar
 *      IRL   Ireland                   NAM   Namibia
 *      IRI   Islamic Rep. of Iran      NCA   Nicaragua   
 *      IRQ   Iraq                      NED   The Netherlands
 *      ISL   Iceland                   NEP   Nepal   
 *      ISR   Israel                    NIG   Niger 
 *      ISV   Virgin Islands            NGR   Nigeria 
 *      ITA   Italy                     NOR   Norway
 *      IVB   British Virgin Islands    NZL   New Zealand
 *      JAM   Jamaica                   OMA   Oman                 
 *      JOR   Jordan                    PAK   Pakistan
 *      JPN   Japan                     PAN   Panama  
 *      KEN   Kenya                     PAR   Paraguay            
 *      KGZ   Kyrghyzstan               PER   Peru            
 *      KOR   Korea (South)             PHI   Philippines
 *      KSA   Saudi Arabia              PNG   Papau-New Guinea
 *      KUW   Kuwait                    POL   Poland 
 *      KZK   Kazakhstan                POR   Portugal    
 *      PRK   Democratic People's       SWE   Sweden
 *            Rep. of Korea             SWZ   Swaziland
 *      PUR   Puerto Rico               SYR   Syria
 *      QAT   Qatar                     TAN   Tanzania
 *      ROM   Romania                   TCH   Czechoslovakia
 *      RSA   South Africa              TGA   Tonga
 *      RUS   Russia                    THA   Thailand
 *      RWA   Rwanda                    TJK   Tadjikistan
 *      SAM   Western Samoa             TOG   Togo
 *      SEN   Senegal                   TPE   Chinese Taipei
 *      SEY   Seychelles                TRI   Trinidad & Tobago
 *      SIN   Singapore                 TUN   Tunisia
 *      SLE   Sierra Leone              TUR   Turkey
 *      SLO   Slovenia                  UAE   United Arab Emirates
 *      SMR   San Marino                UGA   Uganda
 *      SOL   Solomon Islands           UKR   Ukraine
 *      SOM   Somalia                   URU   Uruguay
 *      SRI   Sri Lanka                 USA   United States of
 *      SUD   Sudan                           America
 *      SUI   Switzerland               VAN   Vanuatu
 *      SUR   Surinam                   VEN   Venezuela
 *      VIE   Vietnam
 *      VIN   St. Vincent and the Grenadines
 *      YEM   Yemen
 *      YUG   Yugoslavia
 *      ZAI   Zaire
 *      ZAM   Zambia
 *      ZIM   Zimbabwe
 *     
 */

//  Define the labels used in the GUI
define("FT_SDIF_COUNTRY_CODE_AFGHANISTAN_LABEL", "Afghanistan") ;
define("FT_SDIF_COUNTRY_CODE_ALBANIA_LABEL", "Albania") ;
define("FT_SDIF_COUNTRY_CODE_ALGERIA_LABEL", "Algeria") ;
define("FT_SDIF_COUNTRY_CODE_AMERICAN_SAMOA_LABEL", "American Samoa") ;
define("FT_SDIF_COUNTRY_CODE_ANDORRA_LABEL", "Andorra") ;
define("FT_SDIF_COUNTRY_CODE_ANGOLA_LABEL", "Angola") ;
define("FT_SDIF_COUNTRY_CODE_ANTIGUA_LABEL", "Antigua") ;
define("FT_SDIF_COUNTRY_CODE_ANTILLES_NETHERLANDS_DUTCH_WEST_INDIES_LABEL", "Antilles Netherlands (Dutch West Indies)") ;
define("FT_SDIF_COUNTRY_CODE_ARAB_REPUBLIC_OF_EGYPT_LABEL", "Arab Republic of Egypt") ;
define("FT_SDIF_COUNTRY_CODE_ARGENTINA_LABEL", "Argentina") ;
define("FT_SDIF_COUNTRY_CODE_ARMENIA_LABEL", "Armenia") ;
define("FT_SDIF_COUNTRY_CODE_ARUBA_LABEL", "Aruba") ;
define("FT_SDIF_COUNTRY_CODE_AUSTRALIA_LABEL", "Australia") ;
define("FT_SDIF_COUNTRY_CODE_AUSTRIA_LABEL", "Austria") ;
define("FT_SDIF_COUNTRY_CODE_AZERBAIJAN_LABEL", "Azerbaijan") ;
define("FT_SDIF_COUNTRY_CODE_BAHAMAS_LABEL", "Bahamas") ;
define("FT_SDIF_COUNTRY_CODE_BAHRAIN_LABEL", "Bahrain") ;
define("FT_SDIF_COUNTRY_CODE_BANGLADESH_LABEL", "Bangladesh") ;
define("FT_SDIF_COUNTRY_CODE_BARBADOS_LABEL", "Barbados") ;
define("FT_SDIF_COUNTRY_CODE_BELARUS_LABEL", "Belarus") ;
define("FT_SDIF_COUNTRY_CODE_BELGIUM_LABEL", "Belgium") ;
define("FT_SDIF_COUNTRY_CODE_BELIZE_LABEL", "Belize") ;
define("FT_SDIF_COUNTRY_CODE_BENIN_LABEL", "Benin") ;
define("FT_SDIF_COUNTRY_CODE_BERMUDA_LABEL", "Bermuda") ;
define("FT_SDIF_COUNTRY_CODE_BHUTAN_LABEL", "Bhutan") ;
define("FT_SDIF_COUNTRY_CODE_BOLIVIA_LABEL", "Bolivia") ;
define("FT_SDIF_COUNTRY_CODE_BOTSWANA_LABEL", "Botswana") ;
define("FT_SDIF_COUNTRY_CODE_BRAZIL_LABEL", "Brazil") ;
define("FT_SDIF_COUNTRY_CODE_BRITISH_VIRGIN_ISLANDS_LABEL", "British Virgin Islands") ;
define("FT_SDIF_COUNTRY_CODE_BRUNEI_LABEL", "Brunei") ;
define("FT_SDIF_COUNTRY_CODE_BULGARIA_LABEL", "Bulgaria") ;
define("FT_SDIF_COUNTRY_CODE_BURKINA_FASO_LABEL", "Burkina Faso") ;
define("FT_SDIF_COUNTRY_CODE_CAMEROON_LABEL", "Cameroon") ;
define("FT_SDIF_COUNTRY_CODE_CANADA_LABEL", "Canada") ;
define("FT_SDIF_COUNTRY_CODE_CAYMAN_ISLANDS_LABEL", "Cayman Islands") ;
define("FT_SDIF_COUNTRY_CODE_CENTRAL_AFRICAN_LABEL", "Central African") ;
define("FT_SDIF_COUNTRY_CODE_CHAD_LABEL", "Chad") ;
define("FT_SDIF_COUNTRY_CODE_CHILE_LABEL", "Chile") ;
define("FT_SDIF_COUNTRY_CODE_CHINESE_TAIPEI_LABEL", "Chinese Taipei") ;
define("FT_SDIF_COUNTRY_CODE_COLUMBIA_LABEL", "Columbia") ;
define("FT_SDIF_COUNTRY_CODE_COOK_ISLANDS_LABEL", "Cook Islands") ;
define("FT_SDIF_COUNTRY_CODE_COSTA_RICA_LABEL", "Costa Rica") ;
define("FT_SDIF_COUNTRY_CODE_CROATIA_LABEL", "Croatia") ;
define("FT_SDIF_COUNTRY_CODE_CUBA_LABEL", "Cuba") ;
define("FT_SDIF_COUNTRY_CODE_CYPRUS_LABEL", "Cyprus") ;
define("FT_SDIF_COUNTRY_CODE_CZECHOSLOVAKIA_LABEL", "Czechoslovakia") ;
define("FT_SDIF_COUNTRY_CODE_DEMOCRATIC_PEOPLES_REP_OF_KOREA_LABEL", "Democratic People's Rep. of Korea") ;
define("FT_SDIF_COUNTRY_CODE_DENMARK_LABEL", "Denmark") ;
define("FT_SDIF_COUNTRY_CODE_DJIBOUTI_LABEL", "Djibouti") ;
define("FT_SDIF_COUNTRY_CODE_DOMINICAN_REPUBLIC_LABEL", "Dominican Republic") ;
define("FT_SDIF_COUNTRY_CODE_ECUADOR_LABEL", "Ecuador") ;
define("FT_SDIF_COUNTRY_CODE_EL_SALVADOR_LABEL", "El Salvador") ;
define("FT_SDIF_COUNTRY_CODE_EQUATORIAL_GUINEA_LABEL", "Equatorial Guinea") ;
define("FT_SDIF_COUNTRY_CODE_ESTONIA_LABEL", "Estonia") ;
define("FT_SDIF_COUNTRY_CODE_ETHIOPIA_LABEL", "Ethiopia") ;
define("FT_SDIF_COUNTRY_CODE_FIJI_LABEL", "Fiji") ;
define("FT_SDIF_COUNTRY_CODE_FINLAND_LABEL", "Finland") ;
define("FT_SDIF_COUNTRY_CODE_FRANCE_LABEL", "France") ;
define("FT_SDIF_COUNTRY_CODE_GABON_LABEL", "Gabon") ;
define("FT_SDIF_COUNTRY_CODE_GAMBIA_LABEL", "Gambia") ;
define("FT_SDIF_COUNTRY_CODE_GEORGIA_LABEL", "Georgia") ;
define("FT_SDIF_COUNTRY_CODE_GERMANY_LABEL", "Germany") ;
define("FT_SDIF_COUNTRY_CODE_GHANA_LABEL", "Ghana") ;
define("FT_SDIF_COUNTRY_CODE_GREAT_BRITAIN_LABEL", "Great Britain") ;
define("FT_SDIF_COUNTRY_CODE_GREECE_LABEL", "Greece") ;
define("FT_SDIF_COUNTRY_CODE_GRENADA_LABEL", "Grenada") ;
define("FT_SDIF_COUNTRY_CODE_GUAM_LABEL", "Guam") ;
define("FT_SDIF_COUNTRY_CODE_GUATEMALA_LABEL", "Guatemala") ;
define("FT_SDIF_COUNTRY_CODE_GUINEA_LABEL", "Guinea") ;
define("FT_SDIF_COUNTRY_CODE_GUYANA_LABEL", "Guyana") ;
define("FT_SDIF_COUNTRY_CODE_HAITI_LABEL", "Haiti") ;
define("FT_SDIF_COUNTRY_CODE_HONDURAS_LABEL", "Honduras") ;
define("FT_SDIF_COUNTRY_CODE_HONG_KONG_LABEL", "Hong Kong") ;
define("FT_SDIF_COUNTRY_CODE_HUNGARY_LABEL", "Hungary") ;
define("FT_SDIF_COUNTRY_CODE_ICELAND_LABEL", "Iceland") ;
define("FT_SDIF_COUNTRY_CODE_INDIA_LABEL", "India") ;
define("FT_SDIF_COUNTRY_CODE_INDONESIA_LABEL", "Indonesia") ;
define("FT_SDIF_COUNTRY_CODE_IRAQ_LABEL", "Iraq") ;
define("FT_SDIF_COUNTRY_CODE_IRELAND_LABEL", "Ireland") ;
define("FT_SDIF_COUNTRY_CODE_ISLAMIC_REP_OF_IRAN_LABEL", "Islamic Rep. of Iran") ;
define("FT_SDIF_COUNTRY_CODE_ISRAEL_LABEL", "Israel") ;
define("FT_SDIF_COUNTRY_CODE_ITALY_LABEL", "Italy") ;
define("FT_SDIF_COUNTRY_CODE_IVORY_COAST_LABEL", "Ivory Coast") ;
define("FT_SDIF_COUNTRY_CODE_JAMAICA_LABEL", "Jamaica") ;
define("FT_SDIF_COUNTRY_CODE_JAPAN_LABEL", "Japan") ;
define("FT_SDIF_COUNTRY_CODE_JORDAN_LABEL", "Jordan") ;
define("FT_SDIF_COUNTRY_CODE_KAZAKHSTAN_LABEL", "Kazakhstan") ;
define("FT_SDIF_COUNTRY_CODE_KENYA_LABEL", "Kenya") ;
define("FT_SDIF_COUNTRY_CODE_KOREA_SOUTH_LABEL", "Korea (South)") ;
define("FT_SDIF_COUNTRY_CODE_KUWAIT_LABEL", "Kuwait") ;
define("FT_SDIF_COUNTRY_CODE_KYRGHYZSTAN_LABEL", "Kyrghyzstan") ;
define("FT_SDIF_COUNTRY_CODE_LAOS_LABEL", "Laos") ;
define("FT_SDIF_COUNTRY_CODE_LATVIA_LABEL", "Latvia") ;
define("FT_SDIF_COUNTRY_CODE_LEBANON_LABEL", "Lebanon") ;
define("FT_SDIF_COUNTRY_CODE_LESOTHO_LABEL", "Lesotho") ;
define("FT_SDIF_COUNTRY_CODE_LIBERIA_LABEL", "Liberia") ;
define("FT_SDIF_COUNTRY_CODE_LIBYA_LABEL", "Libya") ;
define("FT_SDIF_COUNTRY_CODE_LIECHTENSTEIN_LABEL", "Liechtenstein") ;
define("FT_SDIF_COUNTRY_CODE_LITHUANIA_LABEL", "Lithuania") ;
define("FT_SDIF_COUNTRY_CODE_LUXEMBOURG_LABEL", "Luxembourg") ;
define("FT_SDIF_COUNTRY_CODE_MADAGASCAR_LABEL", "Madagascar") ;
define("FT_SDIF_COUNTRY_CODE_MALAWI_LABEL", "Malawi") ;
define("FT_SDIF_COUNTRY_CODE_MALAYSIA_LABEL", "Malaysia") ;
define("FT_SDIF_COUNTRY_CODE_MALDIVES_LABEL", "Maldives") ;
define("FT_SDIF_COUNTRY_CODE_MALI_LABEL", "Mali") ;
define("FT_SDIF_COUNTRY_CODE_MALTA_LABEL", "Malta") ;
define("FT_SDIF_COUNTRY_CODE_MAURITANIA_LABEL", "Mauritania") ;
define("FT_SDIF_COUNTRY_CODE_MAURITIUS_LABEL", "Mauritius") ;
define("FT_SDIF_COUNTRY_CODE_MEXICO_LABEL", "Mexico") ;
define("FT_SDIF_COUNTRY_CODE_MOLDOVA_LABEL", "Moldova") ;
define("FT_SDIF_COUNTRY_CODE_MONACO_LABEL", "Monaco") ;
define("FT_SDIF_COUNTRY_CODE_MONGOLIA_LABEL", "Mongolia") ;
define("FT_SDIF_COUNTRY_CODE_MOROCCO_LABEL", "Morocco") ;
define("FT_SDIF_COUNTRY_CODE_MOZAMBIQUE_LABEL", "Mozambique") ;
define("FT_SDIF_COUNTRY_CODE_NAMIBIA_LABEL", "Namibia") ;
define("FT_SDIF_COUNTRY_CODE_NEPAL_LABEL", "Nepal") ;
define("FT_SDIF_COUNTRY_CODE_NEW_ZEALAND_LABEL", "New Zealand") ;
define("FT_SDIF_COUNTRY_CODE_NICARAGUA_LABEL", "Nicaragua") ;
define("FT_SDIF_COUNTRY_CODE_NIGER_LABEL", "Niger") ;
define("FT_SDIF_COUNTRY_CODE_NIGERIA_LABEL", "Nigeria") ;
define("FT_SDIF_COUNTRY_CODE_NORWAY_LABEL", "Norway") ;
define("FT_SDIF_COUNTRY_CODE_OMAN_LABEL", "Oman") ;
define("FT_SDIF_COUNTRY_CODE_PAKISTAN_LABEL", "Pakistan") ;
define("FT_SDIF_COUNTRY_CODE_PANAMA_LABEL", "Panama") ;
define("FT_SDIF_COUNTRY_CODE_PAPAU_NEW_GUINEA_LABEL", "Papau-New Guinea") ;
define("FT_SDIF_COUNTRY_CODE_PARAGUAY_LABEL", "Paraguay") ;
define("FT_SDIF_COUNTRY_CODE_PEOPLES_REP_OF_CHINA_LABEL", "People's Rep. of China") ;
define("FT_SDIF_COUNTRY_CODE_PEOPLES_REP_OF_CONGO_LABEL", "People's Rep. of Congo") ;
define("FT_SDIF_COUNTRY_CODE_PERU_LABEL", "Peru") ;
define("FT_SDIF_COUNTRY_CODE_PHILIPPINES_LABEL", "Philippines") ;
define("FT_SDIF_COUNTRY_CODE_POLAND_LABEL", "Poland") ;
define("FT_SDIF_COUNTRY_CODE_PORTUGAL_LABEL", "Portugal") ;
define("FT_SDIF_COUNTRY_CODE_PUERTO_RICO_LABEL", "Puerto Rico") ;
define("FT_SDIF_COUNTRY_CODE_QATAR_LABEL", "Qatar") ;
define("FT_SDIF_COUNTRY_CODE_REPUBLIC_LABEL", "Republic") ;
define("FT_SDIF_COUNTRY_CODE_ROMANIA_LABEL", "Romania") ;
define("FT_SDIF_COUNTRY_CODE_RUSSIA_LABEL", "Russia") ;
define("FT_SDIF_COUNTRY_CODE_RWANDA_LABEL", "Rwanda") ;
define("FT_SDIF_COUNTRY_CODE_SAN_MARINO_LABEL", "San Marino") ;
define("FT_SDIF_COUNTRY_CODE_SAUDI_ARABIA_LABEL", "Saudi Arabia") ;
define("FT_SDIF_COUNTRY_CODE_SENEGAL_LABEL", "Senegal") ;
define("FT_SDIF_COUNTRY_CODE_SEYCHELLES_LABEL", "Seychelles") ;
define("FT_SDIF_COUNTRY_CODE_SIERRA_LEONE_LABEL", "Sierra Leone") ;
define("FT_SDIF_COUNTRY_CODE_SINGAPORE_LABEL", "Singapore") ;
define("FT_SDIF_COUNTRY_CODE_SLOVENIA_LABEL", "Slovenia") ;
define("FT_SDIF_COUNTRY_CODE_SOLOMON_ISLANDS_LABEL", "Solomon Islands") ;
define("FT_SDIF_COUNTRY_CODE_SOMALIA_LABEL", "Somalia") ;
define("FT_SDIF_COUNTRY_CODE_SOUTH_AFRICA_LABEL", "South Africa") ;
define("FT_SDIF_COUNTRY_CODE_SPAIN_LABEL", "Spain") ;
define("FT_SDIF_COUNTRY_CODE_SRI_LANKA_LABEL", "Sri Lanka") ;
define("FT_SDIF_COUNTRY_CODE_ST_VINCENT_AND_THE_GRENADINES_LABEL", "St. Vincent and the Grenadines") ;
define("FT_SDIF_COUNTRY_CODE_SUDAN_LABEL", "Sudan") ;
define("FT_SDIF_COUNTRY_CODE_SURINAM_LABEL", "Surinam") ;
define("FT_SDIF_COUNTRY_CODE_SWAZILAND_LABEL", "Swaziland") ;
define("FT_SDIF_COUNTRY_CODE_SWEDEN_LABEL", "Sweden") ;
define("FT_SDIF_COUNTRY_CODE_SWITZERLAND_LABEL", "Switzerland") ;
define("FT_SDIF_COUNTRY_CODE_SYRIA_LABEL", "Syria") ;
define("FT_SDIF_COUNTRY_CODE_TADJIKISTAN_LABEL", "Tadjikistan") ;
define("FT_SDIF_COUNTRY_CODE_TANZANIA_LABEL", "Tanzania") ;
define("FT_SDIF_COUNTRY_CODE_THAILAND_LABEL", "Thailand") ;
define("FT_SDIF_COUNTRY_CODE_THE_NETHERLANDS_LABEL", "The Netherlands") ;
define("FT_SDIF_COUNTRY_CODE_TOGO_LABEL", "Togo") ;
define("FT_SDIF_COUNTRY_CODE_TONGA_LABEL", "Tonga") ;
define("FT_SDIF_COUNTRY_CODE_TRINIDAD_AND_TOBAGO_LABEL", "Trinidad & Tobago") ;
define("FT_SDIF_COUNTRY_CODE_TUNISIA_LABEL", "Tunisia") ;
define("FT_SDIF_COUNTRY_CODE_TURKEY_LABEL", "Turkey") ;
define("FT_SDIF_COUNTRY_CODE_UGANDA_LABEL", "Uganda") ;
define("FT_SDIF_COUNTRY_CODE_UKRAINE_LABEL", "Ukraine") ;
define("FT_SDIF_COUNTRY_CODE_UNION_OF_MYANMAR_LABEL", "Union of Myanmar") ;
define("FT_SDIF_COUNTRY_CODE_UNITED_ARAB_EMIRATES_LABEL", "United Arab Emirates") ;
define("FT_SDIF_COUNTRY_CODE_UNITED_STATES_OF_AMERICA_LABEL", "United States of America") ;
define("FT_SDIF_COUNTRY_CODE_URUGUAY_LABEL", "Uruguay") ;
define("FT_SDIF_COUNTRY_CODE_VANUATU_LABEL", "Vanuatu") ;
define("FT_SDIF_COUNTRY_CODE_VENEZUELA_LABEL", "Venezuela") ;
define("FT_SDIF_COUNTRY_CODE_VIETNAM_LABEL", "Vietnam") ;
define("FT_SDIF_COUNTRY_CODE_VIRGIN_ISLANDS_LABEL", "Virgin Islands") ;
define("FT_SDIF_COUNTRY_CODE_WESTERN_SAMOA_LABEL", "Western Samoa") ;
define("FT_SDIF_COUNTRY_CODE_YEMEN_LABEL", "Yemen") ;
define("FT_SDIF_COUNTRY_CODE_YUGOSLAVIA_LABEL", "Yugoslavia") ;
define("FT_SDIF_COUNTRY_CODE_ZAIRE_LABEL", "Zaire") ;
define("FT_SDIF_COUNTRY_CODE_ZAMBIA_LABEL", "Zambia") ;
define("FT_SDIF_COUNTRY_CODE_ZIMBABWE_LABEL", "Zimbabwe") ;

//  Define the values used in the records
define("FT_SDIF_COUNTRY_CODE_AFGHANISTAN_VALUE", "AFG") ;
define("FT_SDIF_COUNTRY_CODE_ALBANIA_VALUE", "ALB") ;
define("FT_SDIF_COUNTRY_CODE_ALGERIA_VALUE", "ALG") ;
define("FT_SDIF_COUNTRY_CODE_AMERICAN_SAMOA_VALUE", "ASA") ;
define("FT_SDIF_COUNTRY_CODE_ANDORRA_VALUE", "AND") ;
define("FT_SDIF_COUNTRY_CODE_ANGOLA_VALUE", "ANG") ;
define("FT_SDIF_COUNTRY_CODE_ANTIGUA_VALUE", "ANT") ;
define("FT_SDIF_COUNTRY_CODE_ANTILLES_NETHERLANDS_DUTCH_WEST_INDIES_VALUE", "AHO") ;
define("FT_SDIF_COUNTRY_CODE_ARAB_REPUBLIC_OF_EGYPT_VALUE", "EGY") ;
define("FT_SDIF_COUNTRY_CODE_ARGENTINA_VALUE", "ARG") ;
define("FT_SDIF_COUNTRY_CODE_ARMENIA_VALUE", "ARM") ;
define("FT_SDIF_COUNTRY_CODE_ARUBA_VALUE", "ARU") ;
define("FT_SDIF_COUNTRY_CODE_AUSTRALIA_VALUE", "AUS") ;
define("FT_SDIF_COUNTRY_CODE_AUSTRIA_VALUE", "AUT") ;
define("FT_SDIF_COUNTRY_CODE_AZERBAIJAN_VALUE", "AZE") ;
define("FT_SDIF_COUNTRY_CODE_BAHAMAS_VALUE", "BAH") ;
define("FT_SDIF_COUNTRY_CODE_BAHRAIN_VALUE", "BRN") ;
define("FT_SDIF_COUNTRY_CODE_BANGLADESH_VALUE", "BAN") ;
define("FT_SDIF_COUNTRY_CODE_BARBADOS_VALUE", "BAR") ;
define("FT_SDIF_COUNTRY_CODE_BELARUS_VALUE", "BLS") ;
define("FT_SDIF_COUNTRY_CODE_BELGIUM_VALUE", "BEL") ;
define("FT_SDIF_COUNTRY_CODE_BELIZE_VALUE", "BIZ") ;
define("FT_SDIF_COUNTRY_CODE_BENIN_VALUE", "BEN") ;
define("FT_SDIF_COUNTRY_CODE_BERMUDA_VALUE", "BER") ;
define("FT_SDIF_COUNTRY_CODE_BHUTAN_VALUE", "BHU") ;
define("FT_SDIF_COUNTRY_CODE_BOLIVIA_VALUE", "BOL") ;
define("FT_SDIF_COUNTRY_CODE_BOTSWANA_VALUE", "BOT") ;
define("FT_SDIF_COUNTRY_CODE_BRAZIL_VALUE", "BRA") ;
define("FT_SDIF_COUNTRY_CODE_BRITISH_VIRGIN_ISLANDS_VALUE", "IVB") ;
define("FT_SDIF_COUNTRY_CODE_BRUNEI_VALUE", "BRU") ;
define("FT_SDIF_COUNTRY_CODE_BULGARIA_VALUE", "BUL") ;
define("FT_SDIF_COUNTRY_CODE_BURKINA_FASO_VALUE", "BUR") ;
define("FT_SDIF_COUNTRY_CODE_CAMEROON_VALUE", "CMR") ;
define("FT_SDIF_COUNTRY_CODE_CANADA_VALUE", "CAN") ;
define("FT_SDIF_COUNTRY_CODE_CAYMAN_ISLANDS_VALUE", "CAY") ;
define("FT_SDIF_COUNTRY_CODE_CENTRAL_AFRICAN_REPUBLIC_VALUE", "CAF") ;
define("FT_SDIF_COUNTRY_CODE_CHAD_VALUE", "CHA") ;
define("FT_SDIF_COUNTRY_CODE_CHILE_VALUE", "CHI") ;
define("FT_SDIF_COUNTRY_CODE_CHINESE_TAIPEI_VALUE", "TPE") ;
define("FT_SDIF_COUNTRY_CODE_COLUMBIA_VALUE", "COL") ;
define("FT_SDIF_COUNTRY_CODE_COOK_ISLANDS_VALUE", "COK") ;
define("FT_SDIF_COUNTRY_CODE_COSTA_RICA_VALUE", "CRC") ;
define("FT_SDIF_COUNTRY_CODE_CROATIA_VALUE", "CRO") ;
define("FT_SDIF_COUNTRY_CODE_CUBA_VALUE", "CUB") ;
define("FT_SDIF_COUNTRY_CODE_CYPRUS_VALUE", "CYP") ;
define("FT_SDIF_COUNTRY_CODE_CZECHOSLOVAKIA_VALUE", "TCH") ;
define("FT_SDIF_COUNTRY_CODE_DEMOCRATIC_PEOPLES_REP_OF_KOREA_VALUE", "PRK") ;
define("FT_SDIF_COUNTRY_CODE_DENMARK_VALUE", "DEN") ;
define("FT_SDIF_COUNTRY_CODE_DJIBOUTI_VALUE", "DJI") ;
define("FT_SDIF_COUNTRY_CODE_DOMINICAN_REPUBLIC_VALUE", "DOM") ;
define("FT_SDIF_COUNTRY_CODE_ECUADOR_VALUE", "ECU") ;
define("FT_SDIF_COUNTRY_CODE_EL_SALVADOR_VALUE", "ESA") ;
define("FT_SDIF_COUNTRY_CODE_EQUATORIAL_GUINEA_VALUE", "GEQ") ;
define("FT_SDIF_COUNTRY_CODE_ESTONIA_VALUE", "EST") ;
define("FT_SDIF_COUNTRY_CODE_ETHIOPIA_VALUE", "ETH") ;
define("FT_SDIF_COUNTRY_CODE_FIJI_VALUE", "FIJ") ;
define("FT_SDIF_COUNTRY_CODE_FINLAND_VALUE", "FIN") ;
define("FT_SDIF_COUNTRY_CODE_FRANCE_VALUE", "FRA") ;
define("FT_SDIF_COUNTRY_CODE_GABON_VALUE", "GAB") ;
define("FT_SDIF_COUNTRY_CODE_GAMBIA_VALUE", "GAM") ;
define("FT_SDIF_COUNTRY_CODE_GEORGIA_VALUE", "GEO") ;
define("FT_SDIF_COUNTRY_CODE_GERMANY_VALUE", "GER") ;
define("FT_SDIF_COUNTRY_CODE_GHANA_VALUE", "GHA") ;
define("FT_SDIF_COUNTRY_CODE_GREAT_BRITAIN_VALUE", "GBR") ;
define("FT_SDIF_COUNTRY_CODE_GREECE_VALUE", "GRE") ;
define("FT_SDIF_COUNTRY_CODE_GRENADA_VALUE", "GRN") ;
define("FT_SDIF_COUNTRY_CODE_GUAM_VALUE", "GUM") ;
define("FT_SDIF_COUNTRY_CODE_GUATEMALA_VALUE", "GUA") ;
define("FT_SDIF_COUNTRY_CODE_GUINEA_VALUE", "GUI") ;
define("FT_SDIF_COUNTRY_CODE_GUYANA_VALUE", "GUY") ;
define("FT_SDIF_COUNTRY_CODE_HAITI_VALUE", "HAI") ;
define("FT_SDIF_COUNTRY_CODE_HONDURAS_VALUE", "HON") ;
define("FT_SDIF_COUNTRY_CODE_HONG_KONG_VALUE", "HKG") ;
define("FT_SDIF_COUNTRY_CODE_HUNGARY_VALUE", "HUN") ;
define("FT_SDIF_COUNTRY_CODE_ICELAND_VALUE", "ISL") ;
define("FT_SDIF_COUNTRY_CODE_INDIA_VALUE", "IND") ;
define("FT_SDIF_COUNTRY_CODE_INDONESIA_VALUE", "INA") ;
define("FT_SDIF_COUNTRY_CODE_IRAQ_VALUE", "IRQ") ;
define("FT_SDIF_COUNTRY_CODE_IRELAND_VALUE", "IRL") ;
define("FT_SDIF_COUNTRY_CODE_ISLAMIC_REP_OF_IRAN_VALUE", "IRI") ;
define("FT_SDIF_COUNTRY_CODE_ISRAEL_VALUE", "ISR") ;
define("FT_SDIF_COUNTRY_CODE_ITALY_VALUE", "ITA") ;
define("FT_SDIF_COUNTRY_CODE_IVORY_COAST_VALUE", "CIV") ;
define("FT_SDIF_COUNTRY_CODE_JAMAICA_VALUE", "JAM") ;
define("FT_SDIF_COUNTRY_CODE_JAPAN_VALUE", "JPN") ;
define("FT_SDIF_COUNTRY_CODE_JORDAN_VALUE", "JOR") ;
define("FT_SDIF_COUNTRY_CODE_KAZAKHSTAN_VALUE", "KZK") ;
define("FT_SDIF_COUNTRY_CODE_KENYA_VALUE", "KEN") ;
define("FT_SDIF_COUNTRY_CODE_KOREA_SOUTH_VALUE", "KOR") ;
define("FT_SDIF_COUNTRY_CODE_KUWAIT_VALUE", "KUW") ;
define("FT_SDIF_COUNTRY_CODE_KYRGHYZSTAN_VALUE", "KGZ") ;
define("FT_SDIF_COUNTRY_CODE_LAOS_VALUE", "LAO") ;
define("FT_SDIF_COUNTRY_CODE_LATVIA_VALUE", "LAT") ;
define("FT_SDIF_COUNTRY_CODE_LEBANON_VALUE", "LIB") ;
define("FT_SDIF_COUNTRY_CODE_LESOTHO_VALUE", "LES") ;
define("FT_SDIF_COUNTRY_CODE_LIBERIA_VALUE", "LBR") ;
define("FT_SDIF_COUNTRY_CODE_LIBYA_VALUE", "LBA") ;
define("FT_SDIF_COUNTRY_CODE_LIECHTENSTEIN_VALUE", "LIE") ;
define("FT_SDIF_COUNTRY_CODE_LITHUANIA_VALUE", "LIT") ;
define("FT_SDIF_COUNTRY_CODE_LUXEMBOURG_VALUE", "LUX") ;
define("FT_SDIF_COUNTRY_CODE_MADAGASCAR_VALUE", "MAD") ;
define("FT_SDIF_COUNTRY_CODE_MALAWI_VALUE", "MAW") ;
define("FT_SDIF_COUNTRY_CODE_MALAYSIA_VALUE", "MAS") ;
define("FT_SDIF_COUNTRY_CODE_MALDIVES_VALUE", "MDV") ;
define("FT_SDIF_COUNTRY_CODE_MALI_VALUE", "MLI") ;
define("FT_SDIF_COUNTRY_CODE_MALTA_VALUE", "MLT") ;
define("FT_SDIF_COUNTRY_CODE_MAURITANIA_VALUE", "MTN") ;
define("FT_SDIF_COUNTRY_CODE_MAURITIUS_VALUE", "MRI") ;
define("FT_SDIF_COUNTRY_CODE_MEXICO_VALUE", "MEX") ;
define("FT_SDIF_COUNTRY_CODE_MOLDOVA_VALUE", "MLD") ;
define("FT_SDIF_COUNTRY_CODE_MONACO_VALUE", "MON") ;
define("FT_SDIF_COUNTRY_CODE_MONGOLIA_VALUE", "MGL") ;
define("FT_SDIF_COUNTRY_CODE_MOROCCO_VALUE", "MAR") ;
define("FT_SDIF_COUNTRY_CODE_MOZAMBIQUE_VALUE", "MOZ") ;
define("FT_SDIF_COUNTRY_CODE_NAMIBIA_VALUE", "NAM") ;
define("FT_SDIF_COUNTRY_CODE_NEPAL_VALUE", "NEP") ;
define("FT_SDIF_COUNTRY_CODE_NEW_ZEALAND_VALUE", "NZL") ;
define("FT_SDIF_COUNTRY_CODE_NICARAGUA_VALUE", "NCA") ;
define("FT_SDIF_COUNTRY_CODE_NIGER_VALUE", "NIG") ;
define("FT_SDIF_COUNTRY_CODE_NIGERIA_VALUE", "NGR") ;
define("FT_SDIF_COUNTRY_CODE_NORWAY_VALUE", "NOR") ;
define("FT_SDIF_COUNTRY_CODE_OMAN_VALUE", "OMA") ;
define("FT_SDIF_COUNTRY_CODE_PAKISTAN_VALUE", "PAK") ;
define("FT_SDIF_COUNTRY_CODE_PANAMA_VALUE", "PAN") ;
define("FT_SDIF_COUNTRY_CODE_PAPAU-NEW_GUINEA_VALUE", "PNG") ;
define("FT_SDIF_COUNTRY_CODE_PARAGUAY_VALUE", "PAR") ;
define("FT_SDIF_COUNTRY_CODE_PEOPLES_REP_OF_CHINA_VALUE", "CHN") ;
define("FT_SDIF_COUNTRY_CODE_PEOPLES_REP_OF_CONGO_VALUE", "CGO") ;
define("FT_SDIF_COUNTRY_CODE_PERU_VALUE", "PER") ;
define("FT_SDIF_COUNTRY_CODE_PHILIPPINES_VALUE", "PHI") ;
define("FT_SDIF_COUNTRY_CODE_POLAND_VALUE", "POL") ;
define("FT_SDIF_COUNTRY_CODE_PORTUGAL_VALUE", "POR") ;
define("FT_SDIF_COUNTRY_CODE_PUERTO_RICO_VALUE", "PUR") ;
define("FT_SDIF_COUNTRY_CODE_QATAR_VALUE", "QAT") ;
define("FT_SDIF_COUNTRY_CODE_ROMANIA_VALUE", "ROM") ;
define("FT_SDIF_COUNTRY_CODE_RUSSIA_VALUE", "RUS") ;
define("FT_SDIF_COUNTRY_CODE_RWANDA_VALUE", "RWA") ;
define("FT_SDIF_COUNTRY_CODE_SAN_MARINO_VALUE", "SMR") ;
define("FT_SDIF_COUNTRY_CODE_SAUDI_ARABIA_VALUE", "KSA") ;
define("FT_SDIF_COUNTRY_CODE_SENEGAL_VALUE", "SEN") ;
define("FT_SDIF_COUNTRY_CODE_SEYCHELLES_VALUE", "SEY") ;
define("FT_SDIF_COUNTRY_CODE_SIERRA_LEONE_VALUE", "SLE") ;
define("FT_SDIF_COUNTRY_CODE_SINGAPORE_VALUE", "SIN") ;
define("FT_SDIF_COUNTRY_CODE_SLOVENIA_VALUE", "SLO") ;
define("FT_SDIF_COUNTRY_CODE_SOLOMON_ISLANDS_VALUE", "SOL") ;
define("FT_SDIF_COUNTRY_CODE_SOMALIA_VALUE", "SOM") ;
define("FT_SDIF_COUNTRY_CODE_SOUTH_AFRICA_VALUE", "RSA") ;
define("FT_SDIF_COUNTRY_CODE_SPAIN_VALUE", "ESP") ;
define("FT_SDIF_COUNTRY_CODE_SRI_LANKA_VALUE", "SRI") ;
define("FT_SDIF_COUNTRY_CODE_ST_VINCENT_AND_THE_GRENADINES_VALUE", "VIN") ;
define("FT_SDIF_COUNTRY_CODE_SUDAN_VALUE", "SUD") ;
define("FT_SDIF_COUNTRY_CODE_SURINAM_VALUE", "SUR") ;
define("FT_SDIF_COUNTRY_CODE_SWAZILAND_VALUE", "SWZ") ;
define("FT_SDIF_COUNTRY_CODE_SWEDEN_VALUE", "SWE") ;
define("FT_SDIF_COUNTRY_CODE_SWITZERLAND_VALUE", "SUI") ;
define("FT_SDIF_COUNTRY_CODE_SYRIA_VALUE", "SYR") ;
define("FT_SDIF_COUNTRY_CODE_TADJIKISTAN_VALUE", "TJK") ;
define("FT_SDIF_COUNTRY_CODE_TANZANIA_VALUE", "TAN") ;
define("FT_SDIF_COUNTRY_CODE_THAILAND_VALUE", "THA") ;
define("FT_SDIF_COUNTRY_CODE_THE_NETHERLANDS_VALUE", "NED") ;
define("FT_SDIF_COUNTRY_CODE_TOGO_VALUE", "TOG") ;
define("FT_SDIF_COUNTRY_CODE_TONGA_VALUE", "TGA") ;
define("FT_SDIF_COUNTRY_CODE_TRINIDAD_AND_TOBAGO_VALUE", "TRI") ;
define("FT_SDIF_COUNTRY_CODE_TUNISIA_VALUE", "TUN") ;
define("FT_SDIF_COUNTRY_CODE_TURKEY_VALUE", "TUR") ;
define("FT_SDIF_COUNTRY_CODE_UGANDA_VALUE", "UGA") ;
define("FT_SDIF_COUNTRY_CODE_UKRAINE_VALUE", "UKR") ;
define("FT_SDIF_COUNTRY_CODE_UNION_OF_MYANMAR_VALUE", "MYA") ;
define("FT_SDIF_COUNTRY_CODE_UNITED_ARAB_EMIRATES_VALUE", "UAE") ;
define("FT_SDIF_COUNTRY_CODE_UNITED_STATES_OF_AMERICA_VALUE", "USA") ;
define("FT_SDIF_COUNTRY_CODE_URUGUAY_VALUE", "URU") ;
define("FT_SDIF_COUNTRY_CODE_VANUATU_VALUE", "VAN") ;
define("FT_SDIF_COUNTRY_CODE_VENEZUELA_VALUE", "VEN") ;
define("FT_SDIF_COUNTRY_CODE_VIETNAM_VALUE", "VIE") ;
define("FT_SDIF_COUNTRY_CODE_VIRGIN_ISLANDS_VALUE", "ISV") ;
define("FT_SDIF_COUNTRY_CODE_WESTERN_SAMOA_VALUE", "SAM") ;
define("FT_SDIF_COUNTRY_CODE_YEMEN_VALUE", "YEM") ;
define("FT_SDIF_COUNTRY_CODE_YUGOSLAVIA_VALUE", "YUG") ;
define("FT_SDIF_COUNTRY_CODE_ZAIRE_VALUE", "ZAI") ;
define("FT_SDIF_COUNTRY_CODE_ZAMBIA_VALUE", "ZAM") ;
define("FT_SDIF_COUNTRY_CODE_ZIMBABWE_VALUE", "ZIM") ;


/**
 *  Meet Type Code
 *
 *  MEET Code 005     Meet Type code
 *       1    Invitational               8    Seniors
 *       2    Regional                   9    Dual
 *       3    LSC Championship           0    Time Trials
 *       4    Zone                       A    International
 *       5    Zone Championship          B    Open
 *       6    National Championship      C    League
 *       7    Juniors
 */

//  Define the labels used in the GUI
define("FT_SDIF_MEET_TYPE_INVITATIONAL_LABEL", "Invitational") ;
define("FT_SDIF_MEET_TYPE_REGIONAL_LABEL", "Regional") ;
define("FT_SDIF_MEET_TYPE_LSC_CHAMPIONSHIP_LABEL", "LSC Championship") ;
define("FT_SDIF_MEET_TYPE_ZONE_LABEL", "Zone") ;
define("FT_SDIF_MEET_TYPE_ZONE_CHAMPIONSHIP_LABEL", "Zone Championship") ;
define("FT_SDIF_MEET_TYPE_NATIONAL_CHAMPIONSHIP_LABEL", "National Championship") ;
define("FT_SDIF_MEET_TYPE_JUNIORS_LABEL", "Juniors") ;
define("FT_SDIF_MEET_TYPE_SENIORS_LABEL", "Seniors") ;
define("FT_SDIF_MEET_TYPE_DUAL_LABEL", "Dual") ;
define("FT_SDIF_MEET_TYPE_TIME_TRIALS_LABEL", "Time Trials") ;
define("FT_SDIF_MEET_TYPE_INTERNATIONAL_LABEL", "International") ;
define("FT_SDIF_MEET_TYPE_OPEN_LABEL", "Open") ;
define("FT_SDIF_MEET_TYPE_LEAGUE_LABEL", "League") ;

//  Define the values used in the records
define("FT_SDIF_MEET_TYPE_INVITATIONAL_VALUE", "1") ;
define("FT_SDIF_MEET_TYPE_REGIONAL_VALUE", "2") ;
define("FT_SDIF_MEET_TYPE_LSC_CHAMPIONSHIP_VALUE", "3") ;
define("FT_SDIF_MEET_TYPE_ZONE_VALUE", "4") ;
define("FT_SDIF_MEET_TYPE_ZONE_CHAMPIONSHIP_VALUE", "5") ;
define("FT_SDIF_MEET_TYPE_NATIONAL_CHAMPIONSHIP_VALUE", "6") ;
define("FT_SDIF_MEET_TYPE_JUNIORS_VALUE", "7") ;
define("FT_SDIF_MEET_TYPE_SENIORS_VALUE", "8") ;
define("FT_SDIF_MEET_TYPE_DUAL_VALUE", "9") ;
define("FT_SDIF_MEET_TYPE_TIME_TRIALS_VALUE", "0") ;
define("FT_SDIF_MEET_TYPE_INTERNATIONAL_VALUE", "A") ;
define("FT_SDIF_MEET_TYPE_OPEN_VALUE", "B") ;
define("FT_SDIF_MEET_TYPE_LEAGUE_VALUE", "C") ;

/**
 * LSC and Team Code
 *
 * TEAM Code 006     LSC and Team code
 *      Supplied from USS Headquarters files upon request.
 *      Concatenation of two-character LSC code and four-character
 *      Team code, in that order (e.g., Colorado's FAST would be
 *      COFAST).  The code for Unattached should always be UN, and
 *      not any other abbreviation.  (Florida Gold's unattached
 *      would be FG  UN.)
 *
 */

/**
 * Region Code
 *
 * REGION Code 007   Region code
 *      1    Region 1                8    Region 8
 *      2    Region 2                9    Region 9
 *      3    Region 3                A    Region 10
 *      4    Region 4                B    Region 11
 *      5    Region 5                C    Region 12
 *      6    Region 6                D    Region 13
 *      7    Region 7                E    Region 14
 */

//  Define the labels used in the GUI
define("FT_SDIF_REGION_CODE_REGION_1_LABEL", "Region 1") ;
define("FT_SDIF_REGION_CODE_REGION_2_LABEL", "Region 2") ;
define("FT_SDIF_REGION_CODE_REGION_3_LABEL", "Region 3") ;
define("FT_SDIF_REGION_CODE_REGION_4_LABEL", "Region 4") ;
define("FT_SDIF_REGION_CODE_REGION_5_LABEL", "Region 5") ;
define("FT_SDIF_REGION_CODE_REGION_6_LABEL", "Region 6") ;
define("FT_SDIF_REGION_CODE_REGION_7_LABEL", "Region 7") ;
define("FT_SDIF_REGION_CODE_REGION_8_LABEL", "Region 8") ;
define("FT_SDIF_REGION_CODE_REGION_9_LABEL", "Region 9") ;
define("FT_SDIF_REGION_CODE_REGION_10_LABEL", "Region 10") ;
define("FT_SDIF_REGION_CODE_REGION_11_LABEL", "Region 11") ;
define("FT_SDIF_REGION_CODE_REGION_12_LABEL", "Region 12") ;
define("FT_SDIF_REGION_CODE_REGION_13_LABEL", "Region 13") ;
define("FT_SDIF_REGION_CODE_REGION_14_LABEL", "Region 14") ;

//  Define the values used in the records
define("FT_SDIF_REGION_CODE_REGION_1_VALUE", "1") ;
define("FT_SDIF_REGION_CODE_REGION_2_VALUE", "2") ;
define("FT_SDIF_REGION_CODE_REGION_3_VALUE", "3") ;
define("FT_SDIF_REGION_CODE_REGION_4_VALUE", "4") ;
define("FT_SDIF_REGION_CODE_REGION_5_VALUE", "5") ;
define("FT_SDIF_REGION_CODE_REGION_6_VALUE", "6") ;
define("FT_SDIF_REGION_CODE_REGION_7_VALUE", "7") ;
define("FT_SDIF_REGION_CODE_REGION_8_VALUE", "8") ;
define("FT_SDIF_REGION_CODE_REGION_9_VALUE", "9") ;
define("FT_SDIF_REGION_CODE_REGION_10_VALUE", "A") ;
define("FT_SDIF_REGION_CODE_REGION_11_VALUE", "B") ;
define("FT_SDIF_REGION_CODE_REGION_12_VALUE", "C") ;
define("FT_SDIF_REGION_CODE_REGION_13_VALUE", "D") ;
define("FT_SDIF_REGION_CODE_REGION_14_VALUE", "E") ;


/**
 * USS Member Number Code
 *
 * USS# Code 008     USS member number code
 *      Refer to USS membership files.  These will not be published.
 */

/**
 * Citizenship Code
 *
 * CITIZEN Code 009  Citizenship code
 *      2AL  Dual:  USA and other country
 *      FGN  Foreign
 *      All codes in COUNTRY Code 004
 */

//  Define the labels used in the GUI
define("FT_SDIF_CITIZENSHIP_CODE_DUAL_LABEL", "USA and Other Country") ;
define("FT_SDIF_CITIZENSHIP_CODE_FOREIGN_LABEL", "Foreign") ;

//  Define the values used in the records
define("FT_SDIF_CITIZENSHIP_CODE_DUAL_VALUE", "2AL") ;
define("FT_SDIF_CITIZENSHIP_CODE_FOREIGN_VALUE", "FGN") ;


/**
 * Swim Sex Code
 *
 * SEX Code 010      Swimmer Sex code
 *      M    Male
 *      F    Female
 */

//  Define the labels used in the GUI
define("FT_SDIF_SWIMMER_SEX_CODE_MALE_LABEL", "Male") ;
define("FT_SDIF_SWIMMER_SEX_CODE_FEMALE_LABEL", "Female") ;

//  Define the values used in the records
define("FT_SDIF_SWIMMER_SEX_CODE_MALE_VALUE", "M") ;
define("FT_SDIF_SWIMMER_SEX_CODE_FEMALE_VALUE", "F") ;


/**
 * Sex of Event Code
 *
 * EVENT SEX Code 011 Sex of Event code
 *      M    Male
 *      F    Female
 *      X    Mixed
 */

//  Define the labels used in the GUI
define("FT_SDIF_EVENT_SEX_CODE_MALE_LABEL", "Male") ;
define("FT_SDIF_EVENT_SEX_CODE_FEMALE_LABEL", "Female") ;
define("FT_SDIF_EVENT_SEX_CODE_MIXED_LABEL", "Mixed") ;

//  Define the values used in the records
define("FT_SDIF_EVENT_SEX_CODE_MALE_VALUE", "M") ;
define("FT_SDIF_EVENT_SEX_CODE_FEMALE_VALUE", "F") ;
define("FT_SDIF_EVENT_SEX_CODE_MIXED_VALUE", "X") ;


/**
 * Event Stroke Code
 *
 * STROKE Code 012   Event Stroke code
 *      1    Freestyle
 *      2    Backstroke
 *      3    Breaststroke
 *      4    Butterfly
 *      5    Individual Medley
 *      6    Freestyle Relay
 *      7    Medley Relay
 */

//  Define the labels used in the GUI
define("FT_SDIF_EVENT_STROKE_CODE_FREESTYLE_LABEL", "Freestyle") ;
define("FT_SDIF_EVENT_STROKE_CODE_BACKSTROKE_LABEL", "Backstroke") ;
define("FT_SDIF_EVENT_STROKE_CODE_BREASTSTROKE_LABEL", "Breaststroke") ;
define("FT_SDIF_EVENT_STROKE_CODE_BUTTERFLY_LABEL", "Butterfly") ;
define("FT_SDIF_EVENT_STROKE_CODE_INDIVIDUAL_MEDLEY_LABEL", "Individual Medley") ;
define("FT_SDIF_EVENT_STROKE_CODE_FREESTYLE_RELAY_LABEL", "Freestyle Relay") ;
define("FT_SDIF_EVENT_STROKE_CODE_MEDLEY_RELAY_LABEL", "Medley Relay") ;

//  Define the values used in the records
define("FT_SDIF_EVENT_STROKE_CODE_FREESTYLE_VALUE", 1) ;
define("FT_SDIF_EVENT_STROKE_CODE_BACKSTROKE_VALUE", 2) ;
define("FT_SDIF_EVENT_STROKE_CODE_BREASTSTROKE_VALUE", 3) ;
define("FT_SDIF_EVENT_STROKE_CODE_BUTTERFLY_VALUE", 4) ;
define("FT_SDIF_EVENT_STROKE_CODE_INDIVIDUAL_MEDLEY_VALUE", 5) ;
define("FT_SDIF_EVENT_STROKE_CODE_FREESTYLE_RELAY_VALUE", 6) ;
define("FT_SDIF_EVENT_STROKE_CODE_MEDLEY_RELAY_VALUE", 7) ;

/**
 * Course/Status Code
 *
 * COURSE Code 013   Course/Status code
 *      Please note that there are alternatives for the three types
 *      of pools.  The alpha characters make the file more readable.
 *      Either may be used.
 *      1 or S   Short Course Meters
 *      2 or Y   Short Course Yards
 *      3 or L   Long Course Meters
 *      X        Disqualified
 *
 * NOTE:  This implementation only uses alpha characters for output
 *        but can accomodate the numeric values for input.
 */

//  Define the labels used in the GUI
define("FT_SDIF_COURSE_STATUS_CODE_SCM_LABEL", "Short Course Meters") ;
define("FT_SDIF_COURSE_STATUS_CODE_SCY_LABEL", "Short Course Yards") ;
define("FT_SDIF_COURSE_STATUS_CODE_LCM_LABEL", "Long Course Meters") ;
define("FT_SDIF_COURSE_STATUS_CODE_DQ_LABEL", "Disqualified") ;

//  Define the values used in the records
define("FT_SDIF_COURSE_STATUS_CODE_SCM_VALUE", "S") ;
define("FT_SDIF_COURSE_STATUS_CODE_SCY_VALUE", "Y") ;
define("FT_SDIF_COURSE_STATUS_CODE_LCM_VALUE", "L") ;
define("FT_SDIF_COURSE_STATUS_CODE_DQ_VALUE", "X") ;
define("FT_SDIF_COURSE_STATUS_CODE_SCM_ALT_VALUE", "1") ;
define("FT_SDIF_COURSE_STATUS_CODE_SCY_ALT_VALUE", "2") ;
define("FT_SDIF_COURSE_STATUS_CODE_LCM_ALT_VALUE", "3") ;

/**
 * Event Time Class Code
 *
 * EVENT TIME CLASS Code 014  Event Time Class code
 *      The following characters are concatenated to form a 2-byte
 *      code for the event time class.  The first character
 *      indicates the lower limit; the second character indicates
 *      the upper limit.  22 indicates B meets, 23 indicates B-A
 *      meets, and 4O indicates AA+ meets.
 *      U    no lower limit (left character only)
 *      O    no upper limit (right character only)
 *      1    Novice times
 *      2    B standard times
 *      P    BB standard times
 *      3    A standard times
 *      4    AA standard times
 *      5    AAA standard times
 *      6    AAAA standard times
 *      J    Junior standard times
 *      S    Senior standard times
 */

//  Define the labels used in the GUI
define("FT_SDIF_TIME_CLASS_CODE_NO_LOWER_LIMIT_LABEL", "no lower limit (left character only)") ;
define("FT_SDIF_TIME_CLASS_CODE_NO_UPPER_LIMIT_LABEL", "no upper limit (right character only)") ;
define("FT_SDIF_TIME_CLASS_CODE_NOVICE_TIMES_LABEL", "Novice times") ;
define("FT_SDIF_TIME_CLASS_CODE_B_STANDARD_TIMES_LABEL", "B standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_BB_STANDARD_TIMES_LABEL", "BB standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_A_STANDARD_TIMES_LABEL", "A standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_AA_STANDARD_TIMES_LABEL", "AA standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_AAA_STANDARD_TIMES_LABEL", "AAA standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_AAAA_STANDARD_TIMES_LABEL", "AAAA standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_JUNIOR_STANDARD_TIMES_LABEL", "Junior standard times") ;
define("FT_SDIF_TIME_CLASS_CODE_SENIOR_STANDARD_TIMES_LABEL", "Senior standard times") ;

//  Define the values used in the records
define("FT_SDIF_TIME_CLASS_CODE_NO_LOWER_LIMIT_VALUE", "U") ;
define("FT_SDIF_TIME_CLASS_CODE_NO_UPPER_LIMIT_VALUE", "0") ;
define("FT_SDIF_TIME_CLASS_CODE_NOVICE_TIMES_VALUE", "1") ;
define("FT_SDIF_TIME_CLASS_CODE_B_STANDARD_TIMES_VALUE", "2") ;
define("FT_SDIF_TIME_CLASS_CODE_BB_STANDARD_TIMES_VALUE", "P") ;
define("FT_SDIF_TIME_CLASS_CODE_A_STANDARD_TIMES_VALUE", "3") ;
define("FT_SDIF_TIME_CLASS_CODE_AA_STANDARD_TIMES_VALUE", "4") ;
define("FT_SDIF_TIME_CLASS_CODE_AAA_STANDARD_TIMES_VALUE", "5") ;
define("FT_SDIF_TIME_CLASS_CODE_AAAA_STANDARD_TIMES_VALUE", "6") ;
define("FT_SDIF_TIME_CLASS_CODE_JUNIOR_STANDARD_TIMES_VALUE", "J") ;
define("FT_SDIF_TIME_CLASS_CODE_SENIOR_STANDARD_TIMES_VALUE", "S") ;

/**
 * Split Code
 *
 * SPLIT Code 015   Split code
 *      C    Cumulative splits supplied
 *      I    Interval splits supplied
 */

//  Define the labels used in the GUI
define("FT_SDIF_SPLIT_CODE_CUMULATIVE_LABEL", "Cumulative") ;
define("FT_SDIF_SPLIT_CODE_INTERVAL_LABEL", "Interval") ;

//  Define the values used in the records
define("FT_SDIF_SPLIT_CODE_CUMULATIVE_VALUE", "C") ;
define("FT_SDIF_SPLIT_CODE_INTERVAL_VALUE", "I") ;

/**
 * Attached Code
 *
 * ATTACH Code 016   Attached code
 *      A    Swimmer is attached to team
 *      U    Swimmer is swimming unattached
 */

//  Define the labels used in the GUI
define("FT_SDIF_ATTACHED_CODE_ATTACHED_LABEL", "Attached") ;
define("FT_SDIF_ATTACHED_CODE_UNATTACHED_LABEL", "Unattached") ;

//  Define the values used in the records
define("FT_SDIF_ATTACHED_CODE_ATTACHED_VALUE", "A") ;
define("FT_SDIF_ATTACHED_CODE_UNATTACHED_VALUE", "U") ;

/**
 * Zone Code
 *
 * ZONE Code 017    Zone code
 *      E    Eastern Zone
 *      S    Southern Zone
 *      C    Central Zone
 *      W    Western Zone
 */

//  Define the labels used in the GUI
define("FT_SDIF_ZONE_CODE_EASTERN_LABEL", "Eastern") ;
define("FT_SDIF_ZONE_CODE_SOUTHERN_LABEL", "Southern") ;
define("FT_SDIF_ZONE_CODE_CENTRAL_LABEL", "Central") ;
define("FT_SDIF_ZONE_CODE_WESTERN_LABEL", "Western") ;

//  Define the values used in the records
define("FT_SDIF_ZONE_CODE_EASTERN_VALUE", "E") ;
define("FT_SDIF_ZONE_CODE_SOUTHERN_VALUE", "S") ;
define("FT_SDIF_ZONE_CODE_CENTRAL_VALUE", "C") ;
define("FT_SDIF_ZONE_CODE_WESTERN_VALUE", "W") ;
  
/**
 * Color Code
 *
 * COLOR Code 018    Color code
 *      GOLD Gold
 *      SILV Silver
 *      BRNZ Bronze
 *      BLUE Blue
 *      RED  Red (note that fourth character is a space)
 *      WHIT White
 */

//  Define the labels used in the GUI
define("FT_SDIF_COLOR_CODE_GOLD_LABEL", "Gold") ;
define("FT_SDIF_COLOR_CODE_SILVER_LABEL", "Silver") ;
define("FT_SDIF_COLOR_CODE_BRONZE_LABEL", "Bronze") ;
define("FT_SDIF_COLOR_CODE_BLUE_LABEL", "Blue") ;
define("FT_SDIF_COLOR_CODE_RED_LABEL", "Red") ;
define("FT_SDIF_COLOR_CODE_WHITE_LABEL", "White") ;

//  Define the values used in the records
define("FT_SDIF_COLOR_CODE_GOLD_VALUE", "GOLD") ;
define("FT_SDIF_COLOR_CODE_SILVER_VALUE", "SILV") ;
define("FT_SDIF_COLOR_CODE_BRONZE_VALUE", "BRNZ") ;
define("FT_SDIF_COLOR_CODE_BLUE_VALUE", "BLUE") ;
define("FT_SDIF_COLOR_CODE_RED_VALUE", "RED ") ;
define("FT_SDIF_COLOR_CODE_WHITE_VALUE", "WHIT") ;

/**
 * Prelims/Finals Code
 *
 * PRELIMS/FINALS Code 019   Prelims/Finals code
 *   P         Prelims
 *   F         Finals
 *   S         Swim-offs
 */

//  Define the labels used in the GUI
define("FT_SDIF_PRELIMS_FINALS_CODE_PRELIMS_LABEL", "Prelims") ;
define("FT_SDIF_PRELIMS_FINALS_CODE_FINALS_LABEL", "Finals") ;
define("FT_SDIF_PRELIMS_FINALS_CODE_SWIM_OFFS_LABEL", "Swim-offs") ;

//  Define the values used in the records
define("FT_SDIF_PRELIMS_FINALS_CODE_PRELIMS_VALUE", "P") ;
define("FT_SDIF_PRELIMS_FINALS_CODE_FINALS_VALUE", "F") ;
define("FT_SDIF_PRELIMS_FINALS_CODE_SWIM_OFFS_VALUE", "S") ;

/**
 * Time Explantion Code
 *
 * TIME Code 020     Time explanation code
 *      NT   No Time
 *      NS   No Swim (or No Show)
 *      DNF  Did Not Finish
 *      DQ   Disqualified
 *      SCR  Scratch
 */

//  Define the labels used in the GUI
define("FT_SDIF_TIME_EXPLANATION_CODE_NO_TIME_LABEL", "No Time") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_NO_SWIM_LABEL", "No Swim") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_DID_NOT_FINISH_LABEL", "Did Not Finish") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_DISQUALIFIED_LABEL", "Disqualified") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_SCRATCH_LABEL", "Scratch") ;

//  Define the values used in the records
define("FT_SDIF_TIME_EXPLANATION_CODE_NO_TIME_VALUE", "NT") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_NO_SWIM_VALUE", "NS") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_DID_NOT_FINISH_VALUE", "DNF") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_DISQUALIFIED_VALUE", "DQ") ;
define("FT_SDIF_TIME_EXPLANATION_CODE_SCRATCH_VALUE", "SCR") ;


/**
 * Membership Code
 *
 * MEMBER Code 021   Membership transaction type
 *      R    Renew
 *      N    New
 *      C    Change
 *      D    Delete
 */

//  Define the labels used in the GUI
define("FT_SDIF_MEMBERSHIP_CODE_RENEW_LABEL", "Renew") ;
define("FT_SDIF_MEMBERSHIP_CODE_NEW_LABEL", "New") ;
define("FT_SDIF_MEMBERSHIP_CODE_CHANGE_LABEL", "Change") ;
define("FT_SDIF_MEMBERSHIP_CODE_DELETE_LABEL", "Delete") ;

//  Define the values used in the records
define("FT_SDIF_MEMBERSHIP_CODE_RENEW_VALUE", "R") ;
define("FT_SDIF_MEMBERSHIP_CODE_NEW_VALUE", "N") ;
define("FT_SDIF_MEMBERSHIP_CODE_CHANGE_VALUE", "C") ;
define("FT_SDIF_MEMBERSHIP_CODE_DELETE_VALUE", "D") ;

/**
 * Season Code
 *
 * SEASON Code 022
 *      1    Season 1
 *      2    Season 2
 *      N    Year-round
 */

//  Define the labels used in the GUI
define("FT_SDIF_SEASON_CODE_SEASON_1_LABEL", "Season 1") ;
define("FT_SDIF_SEASON_CODE_SEASON_2_LABEL", "Season 2") ;
define("FT_SDIF_SEASON_CODE_YEAR_ROUND_LABEL", "Year Round") ;

//  Define the values used in the records
define("FT_SDIF_SEASON_CODE_SEASON_1_VALUE", "1") ;
define("FT_SDIF_SEASON_CODE_SEASON_2_VALUE", "2") ;
define("FT_SDIF_SEASON_CODE_YEAR_ROUND_VALUE", "N") ;

/**
 * Answer Code
 *
 * ANSWER Code 023
 *      Y    Yes
 *      N    No
 */

//  Define the labels used in the GUI
define("FT_SDIF_ANSWER_CODE_YES_LABEL", "Yes") ;
define("FT_SDIF_ANSWER_CODE_NO_LABEL", "No") ;

//  Define the values used in the records
define("FT_SDIF_ANSWER_CODE_YES_VALUE", "Y") ;
define("FT_SDIF_ANSWER_CODE_NO_VALUE", "N") ;

/**
 * Relay Leg Order
 *
 * ORDER Code 024    relay leg order
 *      0    Not on team for this swim
 *      1    First leg
 *      2    Second leg
 *      3    Third leg
 *      4    Fourth leg
 *      A    Alternate
 */

//  Define the labels used in the GUI
define("FT_SDIF_RELAY_CODE_NOT_SWIMMING_LABEL", "Not Swimming") ;
define("FT_SDIF_RELAY_CODE_FIRST_LEG_LABEL", "First Leg") ;
define("FT_SDIF_RELAY_CODE_SECOND_LEG_LABEL", "Second Leg") ;
define("FT_SDIF_RELAY_CODE_THIRD_LEG_LABEL", "Third Leg") ;
define("FT_SDIF_RELAY_CODE_FOURTH_LEG_LABEL", "Fourth Leg") ;
define("FT_SDIF_RELAY_CODE_ALTERNAME_LABEL", "Alternate") ;

//  Define the values used in the records
define("FT_SDIF_RELAY_CODE_NOT_SWIMMING_VALUE", "0") ;
define("FT_SDIF_RELAY_CODE_FIRST_LEG_VALUE", "1") ;
define("FT_SDIF_RELAY_CODE_SECOND_LEG_VALUE", "2") ;
define("FT_SDIF_RELAY_CODE_THIRD_LEG_VALUE", "3") ;
define("FT_SDIF_RELAY_CODE_FOURTH_LEG_VALUE", "4") ;
define("FT_SDIF_RELAY_CODE_ALTERNAME_VALUE", "A") ;


/**
 *
 * EVENT AGE Code 025
 *      first two bytes are lower age limit (digits, or "UN" for no limit)
 *      last two bytes are upper age limit (digits, or "OV" for no limit)
 *      if the age is only one digit, fill with a zero (no blanks allowed)
 */


/**
 *
 * ETHNICITY Code 026
 *      The first byte contains the first ethnicity selection.
 *      The second byte contains an optional second ethnicity selection.
 *      If the first byte contains a V,W or X then the second byte must be blank.   
 *
 *      Q    African American
 *      R    Asian or Pacific Islander
 *      S    Hispanic
 *      U    Native American
 *      V    Other
 *      W    Decline
 *      X    No Responce
 */

//  Define the labels used in the GUI
define("FT_SDIF_ETHNICITY_CODE_AFRICAN_AMERICAN_LABEL", "African American") ;
define("FT_SDIF_ETHNICITY_CODE_ASIA_PAC_RIM_LABEL", "Asian or Pacific Islander") ;
define("FT_SDIF_ETHNICITY_CODE_HISPANIC_LABEL", "Hispanic") ;
define("FT_SDIF_ETHNICITY_CODE_NATIVE_AMERICAN_LABEL", "Native American") ;
define("FT_SDIF_ETHNICITY_CODE_OTHER_LABEL", "Other") ;
define("FT_SDIF_ETHNICITY_CODE_DECLINE_LABEL", "Decline") ;
define("FT_SDIF_ETHNICITY_CODE_NO_RESPONSE_LABEL", "No Response") ;

//  Define the values used in the records
define("FT_SDIF_ETHNICITY_CODE_AFRICAN_AMERICAN_VALUE", "Q") ;
define("FT_SDIF_ETHNICITY_CODE_HISPANIC_VALUE", "S") ;
define("FT_SDIF_ETHNICITY_CODE_NATIVE_AMERICAN_VALUE", "U") ;
define("FT_SDIF_ETHNICITY_CODE_OTHER_VALUE", "V") ;
define("FT_SDIF_ETHNICITY_CODE_DECLINE_VALUE", "W") ;
define("FT_SDIF_ETHNICITY_CODE_NO_RESPONSE_VALUE", "X") ;

/**
 * Each SD3 record is 162 bytes with the first two (2) characters
 * being an alpha-numeric code and the last two (2) characters being
 * a carriage return ASCII(13) and a line feed ASCII(10).  All of the
 * records are fully documented in the specification, refer to it for
 * more details.
 */

//  Define Debug Column Record - used to make sure things are
//  in the correct column - kind of like the old FORTRAN days!
define('FT_SDIF_COLUMN_DEBUG1', '         1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6  ') ;
define('FT_SDIF_COLUMN_DEBUG2', '123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012') ;

//  SDIF record terminator
define('FT_SDIF_RECORD_TERMINATOR', chr(13) . chr(10)) ;

//  Define A0 record
define('FT_SDIF_A0_RECORD', 'A0%1.1s%-8.8s%-2.2s%-30.30s%-20.20s%-10.10s%-20.20s%-12.12s%-8.8s%-42.42s%-2.2s%-3.3s%2.2s') ;

//  Define B1 record
define('FT_SDIF_B1_RECORD', 'B1%1s%8s%30s%22s%22s%20s%2s%10s%3s%1s%8s%8s%4s%8s%1s%10s') ;

//  Define C1 record
define('FT_SDIF_C1_RECORD', 'C1%1.1s%-8.8s%-6.6s%-30.30s%-16.16s%-22.22s%-22.22s%-20.20s%-2.2s%-10.10s%-3.3s%1.1s%-6.6s%1.1s%-10.10s%2.2s') ;

//  Define D1 record
define('FT_SDIF_D1_RECORD', 'D1%1.1s%-8.8s%-6.6s%1.1s%-28.28s%1.1s%-12.12s%1.1s%-3.3s%-8.8s%02.2s%1.1s%-30.30s%-20.20s%-12.12s%-12.12s%-8.8s%1.1s%-3.3s%2.2s') ;

//  Define D2 record
define('FT_SDIF_D2_RECORD', 'D2%1.1s%-8.8s%-6.6s%1.1s%-28.28s%-30.30s%-30.30s%-20.20s%-2.2s%-12.12s%-10.10s%-3.3s%1.1s%1.1s%1.1s%-4.4s%2.2s') ;

//  Define Z0 record
define('FT_SDIF_Z0_RECORD', 'Z0%1.1s%-8.8s%-2.2s%-30.30s%3.3s%3.3s%4.4s%4.4s%6.6s%6.6s%5.5s%6.6s%6.6s%5.5s%3.3s%3.3s%3.3s%3.3s%-57s%-2.2s') ;
?>
