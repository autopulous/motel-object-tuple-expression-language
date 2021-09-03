/*----------------------------------------------------------------------------
  Motel Character
 
  application programmer's types (APT) header file
  ----------------------------------------------------------------------------
  Copyright 2011-2012-2012 John L. Hart IV. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain all copyright notices,
     this list of conditions and the following disclaimer.
 
  2. Redistributions in binary form must reproduce all copyright
     notices, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
 
  THIS SOFTWARE IS PROVIDED BY John L. Hart IV "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
  NO EVENT SHALL John L. Hart IV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
 
  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of John L Hart IV.
  ----------------------------------------------------------------------------*/

#ifndef MOTEL_CHARACTER_T_H
#define MOTEL_CHARACTER_T_H

/*----------------------------------------------------------------------------
  Motel headers
  ----------------------------------------------------------------------------*/

#include "../Motel/motel.compilation.t.h"
#include "../Motel/motel.types.t.h"
#include "../Motel/motel.results.t.h"

#include "../Motel/motel.node.t.h"

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

/*
** Public character members
*/

typedef enum motelCharacterMember
{
	motelCharacterMember_Result,                   /*!< Data type: (motelResult *)
                                                        Description: The method result code */

    motelCharacterMember_Size,                     /*!< Data type: (size_t)
                                                        Description: The size of the character object */

	motelCharacterMember_False,                    /*!< Data type: int
                                                        Description: The false character */

	motelCharacterMember_True,                     /*!< Data type: int
                                                        Description: The true character */

	motelCharacterMember_Zero,                     /*!< Data type: int
                                                        Description: The true character */

	motelCharacterMember_One,                      /*!< Data type: int
                                                        Description: The one character */

	motelCharacterMember_Two,                      /*!< Data type: int
                                                        Description: The two character */

	motelCharacterMember_Three,                    /*!< Data type: int
                                                        Description: The three character */

	motelCharacterMember_Four,                     /*!< Data type: int
                                                        Description: The four character */

	motelCharacterMember_Five,                     /*!< Data type: int
                                                        Description: The five character */

	motelCharacterMember_Six,                      /*!< Data type: int
                                                        Description: The six character */

	motelCharacterMember_Seven,                    /*!< Data type: int
                                                        Description: The seven character */

	motelCharacterMember_Eight,                    /*!< Data type: int
                                                        Description: The eight character */

	motelCharacterMember_Nine,                     /*!< Data type: int
                                                        Description: The nine character */

	motelCharacterMember_Ten,                      /*!< Data type: int
                                                        Description: The ten character */

	motelCharacterMember_Eleven,                   /*!< Data type: int
                                                        Description: The eleven character */

	motelCharacterMember_Tweleve,                  /*!< Data type: int
                                                        Description: The tweleve character */

	motelCharacterMember_Thirteen,                 /*!< Data type: int
                                                        Description: The thirteen character */

	motelCharacterMember_Fourteen,                 /*!< Data type: int
                                                        Description: The fourteen character */

	motelCharacterMember_Fifteen,                  /*!< Data type: int
                                                        Description: The fifteen character */

	motelCharacterMember_Sixteen,                  /*!< Data type: int
                                                        Description: The sixteen character */

	motelCharacterMember_LatinCapitalLetterA,      /*!< Data type: int
                                                        Description: The 'A' character */

	motelCharacterMember_LatinCapitalLetterB,      /*!< Data type: int
                                                        Description: The 'B' character */

	motelCharacterMember_LatinCapitalLetterC,      /*!< Data type: int
                                                        Description: The 'C' character */

	motelCharacterMember_LatinCapitalLetterD,      /*!< Data type: int
                                                        Description: The 'D' character */

	motelCharacterMember_LatinCapitalLetterE,      /*!< Data type: int
                                                        Description: The 'E' character */

	motelCharacterMember_LatinCapitalLetterF,      /*!< Data type: int
                                                        Description: The 'F' character */

	motelCharacterMember_LatinCapitalLetterG,      /*!< Data type: int
                                                        Description: The 'G' character */

	motelCharacterMember_LatinCapitalLetterH,      /*!< Data type: int
                                                        Description: The 'H' character */

	motelCharacterMember_LatinCapitalLetterI,      /*!< Data type: int
                                                        Description: The 'I' character */

    motelCharacterMember_LatinCapitalLetterJ,      /*!< Data type: int
                                                        Description: The 'J' character */

	motelCharacterMember_LatinCapitalLetterK,      /*!< Data type: int
                                                        Description: The 'K' character */

	motelCharacterMember_LatinCapitalLetterL,      /*!< Data type: int
                                                        Description: The 'L' character */

	motelCharacterMember_LatinCapitalLetterM,      /*!< Data type: int
                                                        Description: The 'M' character */

	motelCharacterMember_LatinCapitalLetterN,      /*!< Data type: int
                                                        Description: The 'N' character */

	motelCharacterMember_LatinCapitalLetterO,      /*!< Data type: int
                                                        Description: The 'O' character */

	motelCharacterMember_LatinCapitalLetterP,      /*!< Data type: int
                                                        Description: The 'P' character */

	motelCharacterMember_LatinCapitalLetterQ,      /*!< Data type: int
                                                        Description: The 'Q' character */

	motelCharacterMember_LatinCapitalLetterR,      /*!< Data type: int
                                                        Description: The 'R' character */

	motelCharacterMember_LatinCapitalLetterS,      /*!< Data type: int
                                                        Description: The 'S' character */

	motelCharacterMember_LatinCapitalLetterT,      /*!< Data type: int
                                                        Description: The 'T' character */

	motelCharacterMember_LatinCapitalLetterU,      /*!< Data type: int
                                                        Description: The 'U' character */

	motelCharacterMember_LatinCapitalLetterV,      /*!< Data type: int
                                                        Description: The 'V' character */

	motelCharacterMember_LatinCapitalLetterW,      /*!< Data type: int
                                                        Description: The 'W' character */

	motelCharacterMember_LatinCapitalLetterX,      /*!< Data type: int
                                                        Description: The 'X' character */

	motelCharacterMember_LatinCapitalLetterY,      /*!< Data type: int
                                                        Description: The 'Y' character */

	motelCharacterMember_LatinCapitalLetterZ,      /*!< Data type: int
                                                        Description: The 'Z' character */

	motelCharacterMember_LatinSmallLetterA,        /*!< Data type: int
                                                        Description: The 'a' character */

	motelCharacterMember_LatinSmallLetterB,        /*!< Data type: int
                                                        Description: The 'b' character */

	motelCharacterMember_LatinSmallLetterC,        /*!< Data type: int
                                                        Description: The 'c' character */

	motelCharacterMember_LatinSmallLetterD,        /*!< Data type: int
                                                        Description: The 'd' character */

	motelCharacterMember_LatinSmallLetterE,        /*!< Data type: int
                                                        Description: The 'e' character */

	motelCharacterMember_LatinSmallLetterF,        /*!< Data type: int
                                                        Description: The 'f' character */

	motelCharacterMember_LatinSmallLetterG,        /*!< Data type: int
                                                        Description: The 'g' character */

	motelCharacterMember_LatinSmallLetterH,        /*!< Data type: int
                                                        Description: The 'h' character */

	motelCharacterMember_LatinSmallLetterI,        /*!< Data type: int
                                                        Description: The 'i' character */

	motelCharacterMember_LatinSmallLetterJ,        /*!< Data type: int
                                                        Description: The 'j' character */

	motelCharacterMember_LatinSmallLetterK,        /*!< Data type: int
                                                        Description: The 'k' character */

	motelCharacterMember_LatinSmallLetterL,        /*!< Data type: int
                                                        Description: The 'l' character */

	motelCharacterMember_LatinSmallLetterM,        /*!< Data type: int
                                                        Description: The 'm' character */

	motelCharacterMember_LatinSmallLetterN,        /*!< Data type: int
                                                        Description: The 'n' character */

	motelCharacterMember_LatinSmallLetterO,        /*!< Data type: int
                                                        Description: The 'o' character */

	motelCharacterMember_LatinSmallLetterP,        /*!< Data type: int
                                                        Description: The 'p' character */

	motelCharacterMember_LatinSmallLetterQ,        /*!< Data type: int
                                                        Description: The 'q' character */

	motelCharacterMember_LatinSmallLetterR,        /*!< Data type: int
                                                        Description: The 'r' character */

	motelCharacterMember_LatinSmallLetterS,        /*!< Data type: int
                                                        Description: The 's' character */

	motelCharacterMember_LatinSmallLetterT,        /*!< Data type: int
                                                        Description: The 't' character */

	motelCharacterMember_LatinSmallLetterU,        /*!< Data type: int
                                                        Description: The 'u' character */

	motelCharacterMember_LatinSmallLetterV,        /*!< Data type: int
                                                        Description: The 'v' character */

	motelCharacterMember_LatinSmallLetterW,        /*!< Data type: int
                                                        Description: The 'w' character */

	motelCharacterMember_LatinSmallLetterX,        /*!< Data type: int
                                                        Description: The 'x' character */

	motelCharacterMember_LatinSmallLetterY,        /*!< Data type: int
                                                        Description: The 'y' character */

	motelCharacterMember_LatinSmallLetterZ,        /*!< Data type: int
                                                        Description: The 'z' character */

	motelCharacterMember_LeftCornerBracket,        /*!< Data type: int
                                                        Description: The Left Corner Bracket character */

	motelCharacterMember_RightCornerBracket,       /*!< Data type: int
                                                        Description: The Right Corner Bracket character */

	motelCharacterMember_LeftDoubleAngleBracket,   /*!< Data type: int
                                                        Description: The Left Double Angle Bracket character */

	motelCharacterMember_RightDoubleAngleBracket,  /*!< Data type: int
                                                        Description: The Right Double Angle Bracket character */

	motelCharacterMember_LeftAngleBracket,         /*!< Data type: int
                                                        Description: The Left Angle Bracket character */

	motelCharacterMember_RightAngleBracket,        /*!< Data type: int
                                                        Description: The Right Angle Bracket character */

	motelCharacterMember_LeftSquareBracket,        /*!< Data type: int
                                                        Description: The Left Square Bracket character */

	motelCharacterMember_RightSquareBracket,       /*!< Data type: int
                                                        Description: The Right Square Bracket character */

	motelCharacterMember_LeftCurlyBracket,         /*!< Data type: int
                                                        Description: The Left Curly Bracket character */

	motelCharacterMember_RightCurlyBracket,        /*!< Data type: int
                                                        Description: The Right Curly Bracket character */

	motelCharacterMember_LeftParenthesis,          /*!< Data type: int
                                                        Description: The Left Parenthesis character */

	motelCharacterMember_RightParenthesis,         /*!< Data type: int
                                                        Description: The Right Parenthesis character */

	motelCharacterMember_QuotationMark,            /*!< Data type: int
                                                        Description: The  character */

	motelCharacterMember_LeftDoubleQuotationMark,  /*!< Data type: int
                                                        Description: The Left Double Quotation Mark character */

	motelCharacterMember_RightDoubleQuotationMark, /*!< Data type: int
                                                        Description: The Right Double Quotation Mark character */

	motelCharacterMember_LeftSingleQuotationMark,  /*!< Data type: int
                                                        Description: The Left Single Quotation Mark character */

	motelCharacterMember_RightSingleQuotationMark, /*!< Data type: int
                                                        Description: The Right Single Quotation Mark character */

	motelCharacterMember_Prime,                    /*!< Data type: int
                                                        Description: The Prime character */

	motelCharacterMember_ReversedPrime,            /*!< Data type: int
                                                        Description: The Reversed Prime character */

	motelCharacterMember_DoublePrime,              /*!< Data type: int
                                                        Description: The Double Prime character */

	motelCharacterMember_ReversedDoublePrime,      /*!< Data type: int
                                                        Description: The Reversed Double Prime character */

	motelCharacterMember_TriplePrime,              /*!< Data type: int
                                                        Description: The Triple Prime character */

	motelCharacterMember_ReversedTriplePrime,      /*!< Data type: int
                                                        Description: The Reversed Triple Prime character */

	motelCharacterMember_InvertedQuestionMark,     /*!< Data type: int
                                                        Description: The Inverted Question Mark character */

	motelCharacterMember_QuestionMark,             /*!< Data type: int
                                                        Description: The Question Mark character */

	motelCharacterMember_InvertedExclamationMark,  /*!< Data type: int
                                                        Description: The Inverted Exclamation Mark character */

	motelCharacterMember_ExclamationMark,          /*!< Data type: int
                                                        Description: The Exclamation Mark character */

	motelCharacterMember_DoubleExclamationMark,    /*!< Data type: int
                                                        Description: The Double Exclamation Mark character */

	motelCharacterMember_FullStop,                 /*!< Data type: int
                                                        Description: The Full Stop character */

	motelCharacterMember_Comma,                    /*!< Data type: int
                                                        Description: The Comma character */

	motelCharacterMember_Colon,                    /*!< Data type: int
                                                        Description: The Colon character */

	motelCharacterMember_Semicolon,                /*!< Data type: int
                                                        Description: The Semicolon character */

	motelCharacterMember_ReversedSemicolon,        /*!< Data type: int
                                                        Description: The Reversed Semicolon character */

	motelCharacterMember_Apostrophe,               /*!< Data type: int
                                                        Description: The Apostrophe character */

	motelCharacterMember_HyphenMinus,              /*!< Data type: int
                                                        Description: The Hyphe-Minus character */

	motelCharacterMember_Solidus,                  /*!< Data type: int
                                                        Description: The Solidus character */

	motelCharacterMember_RevereseSolidus,          /*!< Data type: int
                                                        Description: The Reverese Solidus character */

	motelCharacterMember_FractionSlash,            /*!< Data type: int
                                                        Description: The Fraction Slash character */

	motelCharacterMember_Caret,                    /*!< Data type: int
                                                        Description: The Caret character */

	motelCharacterMember_MiddleDot,                /*!< Data type: int
                                                        Description: The Middle Dot character */

	motelCharacterMember_HorizontalEllipsis,       /*!< Data type: int
                                                        Description: The Horizontal Ellipsis character */

	motelCharacterMember_PlusSign,                 /*!< Data type: int
                                                        Description: The Plus Sign character */

	motelCharacterMember_MinusSign,                /*!< Data type: int
                                                        Description: The Minus Sign character */

	motelCharacterMember_MultiplicationSign,       /*!< Data type: int
                                                        Description: The Multiplication Sign character */

	motelCharacterMember_DivisionSign,             /*!< Data type: int
                                                        Description: The Division Sign character */

	motelCharacterMember_SquareRoot,               /*!< Data type: int
                                                        Description: The Square Root character */

	motelCharacterMember_EqualsSign,               /*!< Data type: int
                                                        Description: The Equals Sign character */

	motelCharacterMember_LessThanSign,             /*!< Data type: int
                                                        Description: The Less Than Sign character */

	motelCharacterMember_LessThanOrEqualTo,        /*!< Data type: int
                                                        Description: The Less Than Or Equal To character */

	motelCharacterMember_GreaterThanSign,          /*!< Data type: int
                                                        Description: The Greater Than Sign character */

	motelCharacterMember_GreaterThanOrEqualTo,     /*!< Data type: int
                                                        Description: The Greater Than Or Equal To character */

	motelCharacterMember_NumberSign,               /*!< Data type: int
                                                        Description: The Number Sign character */

	motelCharacterMember_DollarSign,               /*!< Data type: int
                                                        Description: The Dollar Sign character */

	motelCharacterMember_PercentSign,              /*!< Data type: int
                                                        Description: The Percent Sign character */

	motelCharacterMember_Ampersand,                /*!< Data type: int
                                                        Description: The Ampersand character */

	motelCharacterMember_Asterisk,                 /*!< Data type: int
                                                        Description: The Asterisk character */

	motelCharacterMember_CommercialAt,             /*!< Data type: int
                                                        Description: The Commercial At character */

	motelCharacterMember_VerticalLine,             /*!< Data type: int
                                                        Description: The Vertical Line character */

	motelCharacterMember_DoubleVerticalLine,       /*!< Data type: int
                                                        Description: The Double Vertical Line character */

	motelCharacterMember_BrokenBar,                /*!< Data type: int
                                                        Description: The Broken Bar character */

	motelCharacterMember_Tilde,                    /*!< Data type: int
                                                        Description: The Tilde character */

	motelCharacterMember_FigureDash,               /*!< Data type: int
                                                        Description: The Figure Dash character */

	motelCharacterMember_HorizontalBar,            /*!< Data type: int
                                                        Description: The Horizontal Bar character */

	motelCharacterMember_LowLine,                  /*!< Data type: int
                                                        Description: The Low Line character */

	motelCharacterMember_DoubleLowLine,            /*!< Data type: int
                                                        Description: The Double Low Line character */

	motelCharacterMember_DashedLowLine,            /*!< Data type: int
                                                        Description: The Dashed Low Line character */

	motelCharacterMember_CentrelineLowLine,        /*!< Data type: int
                                                        Description: The Centreline Low Line character */

	motelCharacterMember_WavyLowLine,              /*!< Data type: int
                                                        Description: The Wavy LowL ine character */

	motelCharacterMember_Overline,                 /*!< Data type: int
                                                        Description: The Overline character */

	motelCharacterMember_DashedOverline,           /*!< Data type: int
                                                        Description: The Dashed Overline character */

	motelCharacterMember_CentrelineOverline,       /*!< Data type: int
                                                        Description: The Centreline Overline character */

	motelCharacterMember_WavyOverline,             /*!< Data type: int
                                                        Description: The Wavy Overline character */

	motelCharacterMember_DoubleWavyOverline,       /*!< Data type: int
                                                        Description: The Double Wavy Overline character */

	motelCharacterMember_AcuteAccent,              /*!< Data type: int
                                                        Description: The Acute Accent character */

	motelCharacterMember_DoubleAcuteAccent,        /*!< Data type: int
                                                        Description: The Double Acute Accent character */

	motelCharacterMember_GraveAccent,              /*!< Data type: int
                                                        Description: The Grave Accent character */

	motelCharacterMember_CircumflexAccent,         /*!< Data type: int
                                                        Description: The Circumflex Accent character */

	motelCharacterMember_Caron,                    /*!< Data type: int
                                                        Description: The Caron character */

	motelCharacterMember_Breve,                    /*!< Data type: int
                                                        Description: The Breve character */

	motelCharacterMember_Diaresis,                 /*!< Data type: int
                                                        Description: The Diaresis character */

	motelCharacterMember_Ogonek,                   /*!< Data type: int
                                                        Description: The Ogonek character */

	motelCharacterMember_Macron,                   /*!< Data type: int
                                                        Description: The Macron character */

	motelCharacterMember_SmallTilde,               /*!< Data type: int
                                                        Description: The Small Tilde character */

	motelCharacterMember_Cedilla,                  /*!< Data type: int
                                                        Description: The Cedilla character */

	motelCharacterMember_RingAbove,                /*!< Data type: int
                                                        Description: The Ring Above character */

	motelCharacterMember_DotAbove,                 /*!< Data type: int
                                                        Description: The Dot Above character */

	motelCharacterMember_OghamFeatherMark,         /*!< Data type: int
                                                        Description: The Ogham Feather Mark character */

	motelCharacterMember_OghamReversedFeatherMark, /*!< Data type: int
                                                        Description: The Ogham Reversed Feather Mark character */

	motelCharacterMember_Space,                    /*!< Data type: int
                                                        Description: The Space character */

	motelCharacterMember_Backspace,                /*!< Data type: int
                                                        Description: The Backspace character */

	motelCharacterMember_CharacterTabulation,      /*!< Data type: int
                                                        Description: The Character Tabulation character */

	motelCharacterMember_CarriageReturn,           /*!< Data type: int
                                                        Description: The Carriage Return character */

	motelCharacterMember_LineFeed,                 /*!< Data type: int
                                                        Description: The Line Feed character */

	motelCharacterMember_NextLine,                 /*!< Data type: int
                                                        Description: The Next Line character */

	motelCharacterMember_LineSeparator,            /*!< Data type: int
                                                        Description: The Line Separator character */

	motelCharacterMember_ParagraphSeparator,       /*!< Data type: int
                                                        Description: The Paragraph Separator character */

	motelCharacterMember_LineTabulation,           /*!< Data type: int
                                                        Description: The Line Tabulation character */

	motelCharacterMember_FormFeed,                 /*!< Data type: int
                                                        Description: The Form Feed character */

    motelCharacterMember_

} motelCharacterMember;

/*
** standard charcter.sdoc character list
*/

typedef struct motelCharacter motelCharacter;
typedef motelCharacter * motelCharacterHandle;

struct motelCharacter
{
	motelResult result;

    MUTABILITY int false;
    MUTABILITY int true;

    MUTABILITY int zero;
    MUTABILITY int one;
    MUTABILITY int two;
    MUTABILITY int three;
    MUTABILITY int four;
    MUTABILITY int five;
    MUTABILITY int six;
    MUTABILITY int seven;
    MUTABILITY int eight;
    MUTABILITY int nine;
    MUTABILITY int ten;
    MUTABILITY int eleven;
    MUTABILITY int tweleve;
    MUTABILITY int thirteen;
    MUTABILITY int fourteen;
    MUTABILITY int fifteen;
    MUTABILITY int sixteen;

    MUTABILITY int digitZero;
    MUTABILITY int digitOne;
    MUTABILITY int digitTwo;
    MUTABILITY int digitThree;
    MUTABILITY int digitFour;
    MUTABILITY int digitFive;
    MUTABILITY int digitSix;
    MUTABILITY int digitSeven;
    MUTABILITY int digitEight;
    MUTABILITY int digitNine;

    MUTABILITY int latinCapitalLetterA;
    MUTABILITY int latinCapitalLetterB;
    MUTABILITY int latinCapitalLetterC;
    MUTABILITY int latinCapitalLetterD;
    MUTABILITY int latinCapitalLetterE;
    MUTABILITY int latinCapitalLetterF;
    MUTABILITY int latinCapitalLetterG;
    MUTABILITY int latinCapitalLetterH;
    MUTABILITY int latinCapitalLetterI;
    MUTABILITY int latinCapitalLetterJ;
    MUTABILITY int latinCapitalLetterK;
    MUTABILITY int latinCapitalLetterL;
    MUTABILITY int latinCapitalLetterM;
    MUTABILITY int latinCapitalLetterN;
    MUTABILITY int latinCapitalLetterO;
    MUTABILITY int latinCapitalLetterP;
    MUTABILITY int latinCapitalLetterQ;
    MUTABILITY int latinCapitalLetterR;
    MUTABILITY int latinCapitalLetterS;
    MUTABILITY int latinCapitalLetterT;
    MUTABILITY int latinCapitalLetterU;
    MUTABILITY int latinCapitalLetterV;
    MUTABILITY int latinCapitalLetterW;
    MUTABILITY int latinCapitalLetterX;
    MUTABILITY int latinCapitalLetterY;
    MUTABILITY int latinCapitalLetterZ;

    MUTABILITY int latinSmallLetterA;
    MUTABILITY int latinSmallLetterB;
    MUTABILITY int latinSmallLetterC;
    MUTABILITY int latinSmallLetterD;
    MUTABILITY int latinSmallLetterE;
    MUTABILITY int latinSmallLetterF;
    MUTABILITY int latinSmallLetterG;
    MUTABILITY int latinSmallLetterH;
    MUTABILITY int latinSmallLetterI;
    MUTABILITY int latinSmallLetterJ;
    MUTABILITY int latinSmallLetterK;
    MUTABILITY int latinSmallLetterL;
    MUTABILITY int latinSmallLetterM;
    MUTABILITY int latinSmallLetterN;
    MUTABILITY int latinSmallLetterO;
    MUTABILITY int latinSmallLetterP;
    MUTABILITY int latinSmallLetterQ;
    MUTABILITY int latinSmallLetterR;
    MUTABILITY int latinSmallLetterS;
    MUTABILITY int latinSmallLetterT;
    MUTABILITY int latinSmallLetterU;
    MUTABILITY int latinSmallLetterV;
    MUTABILITY int latinSmallLetterW;
    MUTABILITY int latinSmallLetterX;
    MUTABILITY int latinSmallLetterY;
    MUTABILITY int latinSmallLetterZ;

    MUTABILITY int leftCornerBracket;
    MUTABILITY int rightCornerBracket;
    MUTABILITY int leftDoubleAngleBracket;
    MUTABILITY int rightDoubleAngleBracket;
    MUTABILITY int leftAngleBracket;
    MUTABILITY int rightAngleBracket;
    MUTABILITY int leftSquareBracket;
    MUTABILITY int rightSquareBracket;
    MUTABILITY int leftCurlyBracket;
    MUTABILITY int rightCurlyBracket;
    MUTABILITY int leftParenthesis;
    MUTABILITY int rightParenthesis;

    MUTABILITY int quotationMark;
    MUTABILITY int leftDoubleQuotationMark;
    MUTABILITY int rightDoubleQuotationMark;
    MUTABILITY int leftSingleQuotationMark;
    MUTABILITY int rightSingleQuotationMark;
    MUTABILITY int prime;
    MUTABILITY int reversedPrime;
    MUTABILITY int doublePrime;
    MUTABILITY int reversedDoublePrime;
    MUTABILITY int triplePrime;
    MUTABILITY int reversedTriplePrime;

    MUTABILITY int invertedQuestionMark;
    MUTABILITY int questionMark;
    MUTABILITY int invertedExclamationMark;
    MUTABILITY int exclamationMark;
    MUTABILITY int doubleExclamationMark;
    MUTABILITY int fullStop;
    MUTABILITY int comma;
    MUTABILITY int colon;
    MUTABILITY int semicolon;
    MUTABILITY int reversedSemicolon;
    MUTABILITY int apostrophe;
    MUTABILITY int hyphenMinus;
    MUTABILITY int solidus;
    MUTABILITY int revereseSolidus;
    MUTABILITY int fractionSlash;
    MUTABILITY int caret;
    MUTABILITY int middleDot;
    MUTABILITY int horizontalEllipsis;

    MUTABILITY int plusSign;
    MUTABILITY int minusSign;
    MUTABILITY int multiplicationSign;
    MUTABILITY int divisionSign;
    MUTABILITY int squareRoot;
    MUTABILITY int equalsSign;
    MUTABILITY int lessThanSign;
    MUTABILITY int lessThanOrEqualTo;
    MUTABILITY int greaterThanSign;
    MUTABILITY int greaterThanOrEqualTo;

    MUTABILITY int numberSign;
    MUTABILITY int dollarSign;
    MUTABILITY int percentSign;
    MUTABILITY int ampersand;
    MUTABILITY int asterisk;
    MUTABILITY int commercialAt;

    MUTABILITY int verticalLine;
    MUTABILITY int doubleVerticalLine;
    MUTABILITY int brokenBar;
    MUTABILITY int tilde;
    MUTABILITY int figureDash;
    MUTABILITY int horizontalBar;
    MUTABILITY int lowLine;
    MUTABILITY int doubleLowLine;
    MUTABILITY int dashedLowLine;
    MUTABILITY int centrelineLowLine;
    MUTABILITY int wavyLowLine;
    MUTABILITY int overline;
    MUTABILITY int dashedOverline;
    MUTABILITY int centrelineOverline;
    MUTABILITY int wavyOverline;
    MUTABILITY int doubleWavyOverline;

    MUTABILITY int acuteAccent;
    MUTABILITY int doubleAcuteAccent;
    MUTABILITY int graveAccent;
    MUTABILITY int circumflexAccent;
    MUTABILITY int caron;
    MUTABILITY int breve;
    MUTABILITY int diaresis;
    MUTABILITY int ogonek;
    MUTABILITY int macron;
    MUTABILITY int smallTilde;
    MUTABILITY int cedilla;
    MUTABILITY int ringAbove;
    MUTABILITY int dotAbove;

    MUTABILITY int oghamFeatherMark;
    MUTABILITY int oghamReversedFeatherMark;

    MUTABILITY int space;
    MUTABILITY int backspace;
    MUTABILITY int characterTabulation;

    MUTABILITY int carriageReturn;
    MUTABILITY int lineFeed;
    MUTABILITY int nextLine;
    MUTABILITY int lineSeparator;
    MUTABILITY int paragraphSeparator;
    MUTABILITY int lineTabulation;
    MUTABILITY int formFeed;
};

typedef boolean (* _MotelNextCharacter)(motelNodeHandle, byte *);

#endif
