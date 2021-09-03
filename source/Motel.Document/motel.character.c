/*----------------------------------------------------------------------------
  Motel Character
  
  library implementation file
  ----------------------------------------------------------------------------
  Copyright 2011-2012 John L. Hart IV. All rights reserved.
 
  Redistribution and use in source and binary forms; with or without
  modification; are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain all copyright notices;
     this list of conditions and the following disclaimer.
 
  2. Redistributions in binary form must reproduce all copyright
     notices; this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
 
  THIS SOFTWARE IS PROVIDED BY John L. Hart IV "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES; INCLUDING; BUT NOT LIMITED TO; THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
  NO EVENT SHALL John L. Hart IV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT;
  INDIRECT; INCIDENTAL; SPECIAL; EXEMPLARY; OR CONSEQUENTIAL DAMAGES
  (INCLUDING; BUT NOT LIMITED TO; PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE; DATA; OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY; WHETHER IN CONTRACT; STRICT
  LIABILITY; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE; EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
 
  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies; either expressed or implied; of John L Hart IV.
  ----------------------------------------------------------------------------*/

#include "motel.character.h"

/*----------------------------------------------------------------------------
  Embedded copyright
  ----------------------------------------------------------------------------*/

static const char *gCopyright = "@(#)motel.character.c - Copyright 2011-2012 John L. Hart IV - All rights reserved";

/*----------------------------------------------------------------------------
  Public functions
  ----------------------------------------------------------------------------*/

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ValidateCharacter
(
    motelCharacterHandle pCharacter
)
{
    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION ConstructCharacter
(
    motelCharacterHandle * pCharacter
)
{
	/*
	** allocate the character control structure
	*/

    if (!SafeMallocBlock((void **) pCharacter, sizeof(motelCharacter)))
    {
        return (FALSE);
    }

	/*
	** initialize the character control structure
	*/

	(* pCharacter)->result = motelResult_OK;

    /*
    ** standard charcter.sdoc character assignments
    */

    (* pCharacter)->false = FALSE;
    (* pCharacter)->true = TRUE;

    (* pCharacter)->zero = 0;
    (* pCharacter)->one = 1;
    (* pCharacter)->two = 2;
    (* pCharacter)->three = 3;
    (* pCharacter)->four = 4;
    (* pCharacter)->five = 5;
    (* pCharacter)->six = 6;
    (* pCharacter)->seven = 7;
    (* pCharacter)->eight = 8;
    (* pCharacter)->nine = 9;
    (* pCharacter)->ten = 10;
    (* pCharacter)->eleven = 11;
    (* pCharacter)->tweleve = 12;
    (* pCharacter)->thirteen = 13;
    (* pCharacter)->fourteen = 14;
    (* pCharacter)->fifteen = 15;
    (* pCharacter)->sixteen = 16;

    (* pCharacter)->digitZero = '0';
    (* pCharacter)->digitOne = '1';
    (* pCharacter)->digitTwo = '2';
    (* pCharacter)->digitThree = '3';
    (* pCharacter)->digitFour = '4';
    (* pCharacter)->digitFive = '5';
    (* pCharacter)->digitSix = '6';
    (* pCharacter)->digitSeven = '7';
    (* pCharacter)->digitEight = '8';
    (* pCharacter)->digitNine = '9';

    (* pCharacter)->latinCapitalLetterA = 'A';
    (* pCharacter)->latinCapitalLetterB = 'B';
    (* pCharacter)->latinCapitalLetterC = 'C';
    (* pCharacter)->latinCapitalLetterD = 'D';
    (* pCharacter)->latinCapitalLetterE = 'E';
    (* pCharacter)->latinCapitalLetterF = 'F';
    (* pCharacter)->latinCapitalLetterG = 'G';
    (* pCharacter)->latinCapitalLetterH = 'H';
    (* pCharacter)->latinCapitalLetterI = 'I';
    (* pCharacter)->latinCapitalLetterJ = 'J';
    (* pCharacter)->latinCapitalLetterK = 'K';
    (* pCharacter)->latinCapitalLetterL = 'L';
    (* pCharacter)->latinCapitalLetterM = 'M';
    (* pCharacter)->latinCapitalLetterN = 'N';
    (* pCharacter)->latinCapitalLetterO = 'O';
    (* pCharacter)->latinCapitalLetterP = 'P';
    (* pCharacter)->latinCapitalLetterQ = 'Q';
    (* pCharacter)->latinCapitalLetterR = 'R';
    (* pCharacter)->latinCapitalLetterS = 'S';
    (* pCharacter)->latinCapitalLetterT = 'T';
    (* pCharacter)->latinCapitalLetterU = 'U';
    (* pCharacter)->latinCapitalLetterV = 'V';
    (* pCharacter)->latinCapitalLetterW = 'W';
    (* pCharacter)->latinCapitalLetterX = 'X';
    (* pCharacter)->latinCapitalLetterY = 'Y';
    (* pCharacter)->latinCapitalLetterZ = 'Z';

    (* pCharacter)->latinSmallLetterA = 'a';
    (* pCharacter)->latinSmallLetterB = 'b';
    (* pCharacter)->latinSmallLetterC = 'c';
    (* pCharacter)->latinSmallLetterD = 'd';
    (* pCharacter)->latinSmallLetterE = 'e';
    (* pCharacter)->latinSmallLetterF = 'f';
    (* pCharacter)->latinSmallLetterG = 'g';
    (* pCharacter)->latinSmallLetterH = 'h';
    (* pCharacter)->latinSmallLetterI = 'i';
    (* pCharacter)->latinSmallLetterJ = 'j';
    (* pCharacter)->latinSmallLetterK = 'k';
    (* pCharacter)->latinSmallLetterL = 'l';
    (* pCharacter)->latinSmallLetterM = 'm';
    (* pCharacter)->latinSmallLetterN = 'n';
    (* pCharacter)->latinSmallLetterO = 'o';
    (* pCharacter)->latinSmallLetterP = 'p';
    (* pCharacter)->latinSmallLetterQ = 'q';
    (* pCharacter)->latinSmallLetterR = 'r';
    (* pCharacter)->latinSmallLetterS = 's';
    (* pCharacter)->latinSmallLetterT = 't';
    (* pCharacter)->latinSmallLetterU = 'u';
    (* pCharacter)->latinSmallLetterV = 'v';
    (* pCharacter)->latinSmallLetterW = 'w';
    (* pCharacter)->latinSmallLetterX = 'x';
    (* pCharacter)->latinSmallLetterY = 'y';
    (* pCharacter)->latinSmallLetterZ = 'z';

    (* pCharacter)->leftCornerBracket = 0x300C;
    (* pCharacter)->rightCornerBracket = 0x300D;
    (* pCharacter)->leftDoubleAngleBracket = 0x300A;
    (* pCharacter)->rightDoubleAngleBracket = 0x300B;
    (* pCharacter)->leftAngleBracket = 0x3008;
    (* pCharacter)->rightAngleBracket = 0x3009;
    (* pCharacter)->leftSquareBracket = 0x005B;
    (* pCharacter)->rightSquareBracket = 0x005D;
    (* pCharacter)->leftCurlyBracket = 0x007B;
    (* pCharacter)->rightCurlyBracket = 0x007D;
    (* pCharacter)->leftParenthesis = 0x0028;
    (* pCharacter)->rightParenthesis = 0x0029;

    (* pCharacter)->quotationMark = 0x0022;
    (* pCharacter)->leftDoubleQuotationMark = 0x201C;
    (* pCharacter)->rightDoubleQuotationMark = 0x201D;
    (* pCharacter)->leftSingleQuotationMark = 0x2018;
    (* pCharacter)->rightSingleQuotationMark = 0x2019;
    (* pCharacter)->prime = 0x2032;
    (* pCharacter)->reversedPrime = 0x2035;
    (* pCharacter)->doublePrime = 0x2033;
    (* pCharacter)->reversedDoublePrime = 0x2036;
    (* pCharacter)->triplePrime = 0x2034;
    (* pCharacter)->reversedTriplePrime = 0x2037;

    (* pCharacter)->invertedQuestionMark = 0x00BF;
    (* pCharacter)->questionMark = 0x003F;
    (* pCharacter)->invertedExclamationMark = 0x00A1;
    (* pCharacter)->exclamationMark = 0x0021;
    (* pCharacter)->doubleExclamationMark = 0x203C;
    (* pCharacter)->fullStop = 0x002E;
    (* pCharacter)->comma = 0x002C;
    (* pCharacter)->colon = 0x003A;
    (* pCharacter)->semicolon = 0x003B;
    (* pCharacter)->reversedSemicolon = 0x204F;
    (* pCharacter)->apostrophe = 0x0027;
    (* pCharacter)->hyphenMinus = 0x002D;
    (* pCharacter)->solidus = 0x002F;
    (* pCharacter)->revereseSolidus = 0x005C;
    (* pCharacter)->fractionSlash = 0x2044;
    (* pCharacter)->caret = 0x2038;
    (* pCharacter)->middleDot = 0x00B7;
    (* pCharacter)->horizontalEllipsis = 0x2026;

    (* pCharacter)->plusSign = 0x002B;
    (* pCharacter)->minusSign = 0x2212;
    (* pCharacter)->multiplicationSign = 0x00D7;
    (* pCharacter)->divisionSign = 0x00F7;
    (* pCharacter)->squareRoot = 0x221A;
    (* pCharacter)->equalsSign = 0x003D;
    (* pCharacter)->lessThanSign = 0x003C;
    (* pCharacter)->lessThanOrEqualTo = 0x2264;
    (* pCharacter)->greaterThanSign = 0x003E;
    (* pCharacter)->greaterThanOrEqualTo = 0x2265;

    (* pCharacter)->numberSign = 0x0023;
    (* pCharacter)->dollarSign = 0x0024;
    (* pCharacter)->percentSign = 0x0025;
    (* pCharacter)->ampersand = 0x0026;
    (* pCharacter)->asterisk = 0x003A;
    (* pCharacter)->commercialAt = 0x0040;

    (* pCharacter)->verticalLine = 0x007C;
    (* pCharacter)->doubleVerticalLine = 0x2016;
    (* pCharacter)->brokenBar = 0x00A6;
    (* pCharacter)->tilde = 0x007E;
    (* pCharacter)->figureDash = 0x2012;
    (* pCharacter)->horizontalBar = 0x2015;
    (* pCharacter)->lowLine = 0x005F;
    (* pCharacter)->doubleLowLine = 0x2017;
    (* pCharacter)->dashedLowLine = 0xFE4D;
    (* pCharacter)->centrelineLowLine = 0xFE4E;
    (* pCharacter)->wavyLowLine = 0xFE4F;
    (* pCharacter)->overline = 0x203E;
    (* pCharacter)->dashedOverline = 0xFE49;
    (* pCharacter)->centrelineOverline = 0xFE4A;
    (* pCharacter)->wavyOverline = 0xFE4B;
    (* pCharacter)->doubleWavyOverline = 0xFE4C;

    (* pCharacter)->acuteAccent = 0x00B4;
    (* pCharacter)->doubleAcuteAccent = 0x02DD;
    (* pCharacter)->graveAccent = 0x0060;
    (* pCharacter)->circumflexAccent = 0x005E;
    (* pCharacter)->caron = 0x02C7;
    (* pCharacter)->breve = 0x02D8;
    (* pCharacter)->diaresis = 0x00A8;
    (* pCharacter)->ogonek = 0x02DB;
    (* pCharacter)->macron = 0x00AF;
    (* pCharacter)->smallTilde = 0x02DC;
    (* pCharacter)->cedilla = 0x00B8;
    (* pCharacter)->ringAbove = 0x02DA;
    (* pCharacter)->dotAbove = 0x02D9;

    (* pCharacter)->oghamFeatherMark = 0x169B;
    (* pCharacter)->oghamReversedFeatherMark = 0x169C;

    (* pCharacter)->space = 0x0020;
    (* pCharacter)->backspace = 0x0008;
    (* pCharacter)->characterTabulation = 0x0009;

    (* pCharacter)->carriageReturn = 0x000D;
    (* pCharacter)->lineFeed = 0x000A;
    (* pCharacter)->nextLine = 0x0085;
    (* pCharacter)->lineSeparator = 0x2028;
    (* pCharacter)->paragraphSeparator = 0x2029;
    (* pCharacter)->lineTabulation = 0x000B;
    (* pCharacter)->formFeed = 0x000C;

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION DestructCharacter
(
    motelCharacterHandle * pCharacter
)
{
    /*
    ** there is no character
    */

    if (NULL == pCharacter || NULL == * pCharacter)
	{
		return (FALSE);
	}

	/*
	** release the character control structure
	*/

    SafeFreeBlock((void **) pCharacter);

    return (TRUE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION SetCharacterMember
(
    motelCharacterHandle pCharacter,
	motelCharacterMember pMember,
	const void * pValue
)
{
    /*
    ** there is no character object
    */

	if (NULL == pCharacter)
	{
		return (FALSE);
	}

	pCharacter->result = motelResult_OK;

	if (NULL == pValue)
	{
		pCharacter->result = motelResult_NullPointer;

		return (FALSE);
	}

	switch (pMember)
	{
        case motelCharacterMember_False:

            pCharacter->false = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_True:

            pCharacter->true = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Zero:

            pCharacter->zero = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_One:

            pCharacter->one = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Two:

            pCharacter->two = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Three:

            pCharacter->three = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Four:

            pCharacter->four = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Five:

            pCharacter->five = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Six:

            pCharacter->six = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Seven:

            pCharacter->seven = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Eight:

            pCharacter->eight = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Nine:

            pCharacter->nine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Ten:

            pCharacter->ten = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Eleven:

            pCharacter->eleven = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Tweleve:

            pCharacter->tweleve = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Thirteen:

            pCharacter->thirteen = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Fourteen:

            pCharacter->fourteen = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Fifteen:

            pCharacter->fifteen = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Sixteen:

            pCharacter->sixteen = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterA:

            pCharacter->latinCapitalLetterA = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterB:

            pCharacter->latinCapitalLetterB = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterC:

            pCharacter->latinCapitalLetterC = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterD:

            pCharacter->latinCapitalLetterD = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterE:

            pCharacter->latinCapitalLetterE = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterF:

            pCharacter->latinCapitalLetterF = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterG:

            pCharacter->latinCapitalLetterG = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterH:

            pCharacter->latinCapitalLetterH = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterI:

            pCharacter->latinCapitalLetterI = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterJ:

            pCharacter->latinCapitalLetterJ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterK:

            pCharacter->latinCapitalLetterK = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterL:

            pCharacter->latinCapitalLetterL = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterM:

            pCharacter->latinCapitalLetterM = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterN:

            pCharacter->latinCapitalLetterN = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterO:

            pCharacter->latinCapitalLetterO = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterP:

            pCharacter->latinCapitalLetterP = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterQ:

            pCharacter->latinCapitalLetterQ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterR:

            pCharacter->latinCapitalLetterR = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterS:

            pCharacter->latinCapitalLetterS = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterT:

            pCharacter->latinCapitalLetterT = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterU:

            pCharacter->latinCapitalLetterU = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterV:

            pCharacter->latinCapitalLetterV = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterW:

            pCharacter->latinCapitalLetterW = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterX:

            pCharacter->latinCapitalLetterX = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterY:

            pCharacter->latinCapitalLetterY = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterZ:

            pCharacter->latinCapitalLetterZ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterA:

            pCharacter->latinSmallLetterA = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterB:

            pCharacter->latinSmallLetterB = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterC:

            pCharacter->latinSmallLetterC = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterD:

            pCharacter->latinSmallLetterD = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterE:

            pCharacter->latinSmallLetterE = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterF:

            pCharacter->latinSmallLetterF = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterG:

            pCharacter->latinSmallLetterG = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterH:

            pCharacter->latinSmallLetterH = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterI:

            pCharacter->latinSmallLetterI = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterJ:

            pCharacter->latinSmallLetterJ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterK:

            pCharacter->latinSmallLetterK = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterL:

            pCharacter->latinSmallLetterL = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterM:

            pCharacter->latinSmallLetterM = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterN:

            pCharacter->latinSmallLetterN = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterO:

            pCharacter->latinSmallLetterO = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterP:

            pCharacter->latinSmallLetterP = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterQ:

            pCharacter->latinSmallLetterQ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterR:

            pCharacter->latinSmallLetterR = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterS:

            pCharacter->latinSmallLetterS = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterT:

            pCharacter->latinSmallLetterT = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterU:

            pCharacter->latinSmallLetterU = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterV:

            pCharacter->latinSmallLetterV = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterW:

            pCharacter->latinSmallLetterW = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterX:

            pCharacter->latinSmallLetterX = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterY:

            pCharacter->latinSmallLetterY = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterZ:

            pCharacter->latinSmallLetterZ = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftCornerBracket:

            pCharacter->leftCornerBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightCornerBracket:

            pCharacter->rightCornerBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftDoubleAngleBracket:

            pCharacter->leftDoubleAngleBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightDoubleAngleBracket:

            pCharacter->rightDoubleAngleBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftAngleBracket:

            pCharacter->leftAngleBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightAngleBracket:

            pCharacter->rightAngleBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftSquareBracket:

            pCharacter->leftSquareBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightSquareBracket:

            pCharacter->rightSquareBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftCurlyBracket:

            pCharacter->leftCurlyBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightCurlyBracket:

            pCharacter->rightCurlyBracket = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftParenthesis:

            pCharacter->leftParenthesis = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightParenthesis:

            pCharacter->rightParenthesis = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_QuotationMark:

            pCharacter->quotationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftDoubleQuotationMark:

            pCharacter->leftDoubleQuotationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightDoubleQuotationMark:

            pCharacter->rightDoubleQuotationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LeftSingleQuotationMark:

            pCharacter->leftSingleQuotationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RightSingleQuotationMark:

            pCharacter->rightSingleQuotationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Prime:

            pCharacter->prime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ReversedPrime:

            pCharacter->reversedPrime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoublePrime:

            pCharacter->doublePrime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ReversedDoublePrime:

            pCharacter->reversedDoublePrime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_TriplePrime:

            pCharacter->triplePrime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ReversedTriplePrime:

            pCharacter->reversedTriplePrime = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_InvertedQuestionMark:

            pCharacter->invertedQuestionMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_QuestionMark:

            pCharacter->questionMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_InvertedExclamationMark:

            pCharacter->invertedExclamationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ExclamationMark:

            pCharacter->exclamationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoubleExclamationMark:

            pCharacter->doubleExclamationMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_FullStop:

            pCharacter->fullStop = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Comma:

            pCharacter->comma = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Colon:

            pCharacter->colon = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Semicolon:

            pCharacter->semicolon = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ReversedSemicolon:

            pCharacter->reversedSemicolon = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Apostrophe:

            pCharacter->apostrophe = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_HyphenMinus:

            pCharacter->hyphenMinus = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Solidus:

            pCharacter->solidus = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RevereseSolidus:

            pCharacter->revereseSolidus = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_FractionSlash:

            pCharacter->fractionSlash = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Caret:

            pCharacter->caret = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_MiddleDot:

            pCharacter->middleDot = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_HorizontalEllipsis:

            pCharacter->horizontalEllipsis = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_PlusSign:

            pCharacter->plusSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_MinusSign:

            pCharacter->minusSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_MultiplicationSign:

            pCharacter->multiplicationSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DivisionSign:

            pCharacter->divisionSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_SquareRoot:

            pCharacter->squareRoot = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_EqualsSign:

            pCharacter->equalsSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LessThanSign:

            pCharacter->lessThanSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LessThanOrEqualTo:

            pCharacter->lessThanOrEqualTo = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_GreaterThanSign:

            pCharacter->greaterThanSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_GreaterThanOrEqualTo:

            pCharacter->greaterThanOrEqualTo = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_NumberSign:

            pCharacter->numberSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DollarSign:

            pCharacter->dollarSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_PercentSign:

            pCharacter->percentSign = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Ampersand:

            pCharacter->ampersand = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Asterisk:

            pCharacter->asterisk = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CommercialAt:

            pCharacter->commercialAt = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_VerticalLine:

            pCharacter->verticalLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoubleVerticalLine:

            pCharacter->doubleVerticalLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_BrokenBar:

            pCharacter->brokenBar = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Tilde:
                
            pCharacter->tilde = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_FigureDash:
                
            pCharacter->figureDash = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_HorizontalBar:
                
            pCharacter->horizontalBar = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LowLine:

            pCharacter->lowLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoubleLowLine:

            pCharacter->doubleLowLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DashedLowLine:

            pCharacter->dashedLowLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CentrelineLowLine:

            pCharacter->centrelineLowLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_WavyLowLine:

            pCharacter->wavyLowLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Overline:

            pCharacter->overline = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DashedOverline:

            pCharacter->dashedOverline = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CentrelineOverline:

            pCharacter->centrelineOverline = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_WavyOverline:

            pCharacter->wavyOverline = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoubleWavyOverline:

            pCharacter->doubleWavyOverline = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_AcuteAccent:

            pCharacter->acuteAccent = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DoubleAcuteAccent:

            pCharacter->doubleAcuteAccent = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_GraveAccent:

            pCharacter->graveAccent = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CircumflexAccent:

            pCharacter->circumflexAccent = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Caron:

            pCharacter->caron = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Breve:

            pCharacter->breve = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Diaresis:

            pCharacter->diaresis = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Ogonek:

            pCharacter->ogonek = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Macron:

            pCharacter->macron = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_SmallTilde:

            pCharacter->smallTilde = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Cedilla:

            pCharacter->cedilla = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_RingAbove:

            pCharacter->ringAbove = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_DotAbove:

            pCharacter->dotAbove = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_OghamFeatherMark:

            pCharacter->oghamFeatherMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_OghamReversedFeatherMark:

            pCharacter->oghamReversedFeatherMark = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Space:

            pCharacter->space = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_Backspace:

            pCharacter->backspace = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CharacterTabulation:

            pCharacter->characterTabulation = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_CarriageReturn:

            pCharacter->carriageReturn = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LineFeed:

            pCharacter->lineFeed = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_NextLine:

            pCharacter->nextLine = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LineSeparator:

            pCharacter->lineSeparator = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_ParagraphSeparator:

            pCharacter->paragraphSeparator = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_LineTabulation:

            pCharacter->lineTabulation = (int) (* (int *) pValue);

            return (TRUE);

        case motelCharacterMember_FormFeed:

            pCharacter->formFeed = (int) (* (int *) pValue);

            return (TRUE);
	}

	pCharacter->result = motelResult_InvalidMember;

	return (FALSE);
}

EXPORT_STORAGE_CLASS success CALLING_CONVENTION GetCharacterMember
(
    motelCharacterHandle pCharacter,
	motelCharacterMember pMember,
	void * pValue
)
{
    /*
    ** there is no character object
    */

	if (NULL == pCharacter)
	{
		return (FALSE);
	}

	/*
	** no return parameter
	*/

	if (NULL == pValue)
	{
		return (FALSE);
	}

	/*
	** result code is a special case because we want to set a result code for GetCharacterMember()
	*/

    if (motelCharacterMember_Result == pMember)
    {
		* (motelResult *) pValue = pCharacter->result;

		return (TRUE);
    }

    /*
    ** get member
    */

	pCharacter->result = motelResult_OK;

	switch (pMember)
	{
		case motelCharacterMember_Size:

            * (size_t *) pValue = sizeof(motelCharacter);

			return (TRUE);

        case motelCharacterMember_False:

            * (int *) pValue = pCharacter->false;

            return (TRUE);

        case motelCharacterMember_True:

            * (int *) pValue = pCharacter->true;

            return (TRUE);

        case motelCharacterMember_Zero:

            * (int *) pValue = pCharacter->zero;

            return (TRUE);

        case motelCharacterMember_One:

            * (int *) pValue = pCharacter->one;

            return (TRUE);

        case motelCharacterMember_Two:

            * (int *) pValue = pCharacter->two;

            return (TRUE);

        case motelCharacterMember_Three:

            * (int *) pValue = pCharacter->three;

            return (TRUE);

        case motelCharacterMember_Four:

            * (int *) pValue = pCharacter->four;

            return (TRUE);

        case motelCharacterMember_Five:

            * (int *) pValue = pCharacter->five;

            return (TRUE);

        case motelCharacterMember_Six:

            * (int *) pValue = pCharacter->six;

            return (TRUE);

        case motelCharacterMember_Seven:

            * (int *) pValue = pCharacter->seven;

            return (TRUE);

        case motelCharacterMember_Eight:

            * (int *) pValue = pCharacter->eight;

            return (TRUE);

        case motelCharacterMember_Nine:

            * (int *) pValue = pCharacter->nine;

            return (TRUE);

        case motelCharacterMember_Ten:

            * (int *) pValue = pCharacter->ten;

            return (TRUE);

        case motelCharacterMember_Eleven:

            * (int *) pValue = pCharacter->eleven;

            return (TRUE);

        case motelCharacterMember_Tweleve:

            * (int *) pValue = pCharacter->tweleve;

            return (TRUE);

        case motelCharacterMember_Thirteen:

            * (int *) pValue = pCharacter->thirteen;

            return (TRUE);

        case motelCharacterMember_Fourteen:

            * (int *) pValue = pCharacter->fourteen;

            return (TRUE);

        case motelCharacterMember_Fifteen:

            * (int *) pValue = pCharacter->fifteen;

            return (TRUE);

        case motelCharacterMember_Sixteen:

            * (int *) pValue = pCharacter->sixteen;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterA:

            * (int *) pValue = pCharacter->latinCapitalLetterA;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterB:

            * (int *) pValue = pCharacter->latinCapitalLetterB;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterC:

            * (int *) pValue = pCharacter->latinCapitalLetterC;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterD:

            * (int *) pValue = pCharacter->latinCapitalLetterD;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterE:

            * (int *) pValue = pCharacter->latinCapitalLetterE;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterF:

            * (int *) pValue = pCharacter->latinCapitalLetterF;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterG:

            * (int *) pValue = pCharacter->latinCapitalLetterG;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterH:

            * (int *) pValue = pCharacter->latinCapitalLetterH;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterI:

            * (int *) pValue = pCharacter->latinCapitalLetterI;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterJ:

            * (int *) pValue = pCharacter->latinCapitalLetterJ;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterK:

            * (int *) pValue = pCharacter->latinCapitalLetterK;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterL:

            * (int *) pValue = pCharacter->latinCapitalLetterL;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterM:

            * (int *) pValue = pCharacter->latinCapitalLetterM;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterN:

            * (int *) pValue = pCharacter->latinCapitalLetterN;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterO:

            * (int *) pValue = pCharacter->latinCapitalLetterO;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterP:

            * (int *) pValue = pCharacter->latinCapitalLetterP;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterQ:

            * (int *) pValue = pCharacter->latinCapitalLetterQ;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterR:

            * (int *) pValue = pCharacter->latinCapitalLetterR;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterS:

            * (int *) pValue = pCharacter->latinCapitalLetterS;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterT:

            * (int *) pValue = pCharacter->latinCapitalLetterT;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterU:

            * (int *) pValue = pCharacter->latinCapitalLetterU;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterV:

            * (int *) pValue = pCharacter->latinCapitalLetterV;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterW:

            * (int *) pValue = pCharacter->latinCapitalLetterW;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterX:

            * (int *) pValue = pCharacter->latinCapitalLetterX;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterY:

            * (int *) pValue = pCharacter->latinCapitalLetterY;

            return (TRUE);

        case motelCharacterMember_LatinCapitalLetterZ:

            * (int *) pValue = pCharacter->latinCapitalLetterZ;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterA:

            * (int *) pValue = pCharacter->latinSmallLetterA;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterB:

            * (int *) pValue = pCharacter->latinSmallLetterB;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterC:

            * (int *) pValue = pCharacter->latinSmallLetterC;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterD:

            * (int *) pValue = pCharacter->latinSmallLetterD;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterE:

            * (int *) pValue = pCharacter->latinSmallLetterE;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterF:

            * (int *) pValue = pCharacter->latinSmallLetterF;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterG:

            * (int *) pValue = pCharacter->latinSmallLetterG;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterH:

            * (int *) pValue = pCharacter->latinSmallLetterH;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterI:

            * (int *) pValue = pCharacter->latinSmallLetterI;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterJ:

            * (int *) pValue = pCharacter->latinSmallLetterJ;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterK:

            * (int *) pValue = pCharacter->latinSmallLetterK;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterL:

            * (int *) pValue = pCharacter->latinSmallLetterL;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterM:

            * (int *) pValue = pCharacter->latinSmallLetterM;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterN:

            * (int *) pValue = pCharacter->latinSmallLetterN;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterO:

            * (int *) pValue = pCharacter->latinSmallLetterO;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterP:

            * (int *) pValue = pCharacter->latinSmallLetterP;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterQ:

            * (int *) pValue = pCharacter->latinSmallLetterQ;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterR:

            * (int *) pValue = pCharacter->latinSmallLetterR;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterS:

            * (int *) pValue = pCharacter->latinSmallLetterS;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterT:

            * (int *) pValue = pCharacter->latinSmallLetterT;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterU:

            * (int *) pValue = pCharacter->latinSmallLetterU;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterV:

            * (int *) pValue = pCharacter->latinSmallLetterV;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterW:

            * (int *) pValue = pCharacter->latinSmallLetterW;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterX:

            * (int *) pValue = pCharacter->latinSmallLetterX;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterY:

            * (int *) pValue = pCharacter->latinSmallLetterY;

            return (TRUE);

        case motelCharacterMember_LatinSmallLetterZ:

            * (int *) pValue = pCharacter->latinSmallLetterZ;

            return (TRUE);

        case motelCharacterMember_LeftCornerBracket:

            * (int *) pValue = pCharacter->leftCornerBracket;

            return (TRUE);

        case motelCharacterMember_RightCornerBracket:

            * (int *) pValue = pCharacter->rightCornerBracket;

            return (TRUE);

        case motelCharacterMember_LeftDoubleAngleBracket:

            * (int *) pValue = pCharacter->leftDoubleAngleBracket;

            return (TRUE);

        case motelCharacterMember_RightDoubleAngleBracket:

            * (int *) pValue = pCharacter->rightDoubleAngleBracket;

            return (TRUE);

        case motelCharacterMember_LeftAngleBracket:

            * (int *) pValue = pCharacter->leftAngleBracket;

            return (TRUE);

        case motelCharacterMember_RightAngleBracket:

            * (int *) pValue = pCharacter->rightAngleBracket;

            return (TRUE);

        case motelCharacterMember_LeftSquareBracket:

            * (int *) pValue = pCharacter->leftSquareBracket;

            return (TRUE);

        case motelCharacterMember_RightSquareBracket:

            * (int *) pValue = pCharacter->rightSquareBracket;

            return (TRUE);

        case motelCharacterMember_LeftCurlyBracket:

            * (int *) pValue = pCharacter->leftCurlyBracket;

            return (TRUE);

        case motelCharacterMember_RightCurlyBracket:

            * (int *) pValue = pCharacter->rightCurlyBracket;

            return (TRUE);

        case motelCharacterMember_LeftParenthesis:

            * (int *) pValue = pCharacter->leftParenthesis;

            return (TRUE);

        case motelCharacterMember_RightParenthesis:

            * (int *) pValue = pCharacter->rightParenthesis;

            return (TRUE);

        case motelCharacterMember_QuotationMark:

            * (int *) pValue = pCharacter->quotationMark;

            return (TRUE);

        case motelCharacterMember_LeftDoubleQuotationMark:

            * (int *) pValue = pCharacter->leftDoubleQuotationMark;

            return (TRUE);

        case motelCharacterMember_RightDoubleQuotationMark:

            * (int *) pValue = pCharacter->rightDoubleQuotationMark;

            return (TRUE);

        case motelCharacterMember_LeftSingleQuotationMark:

            * (int *) pValue = pCharacter->leftSingleQuotationMark;

            return (TRUE);

        case motelCharacterMember_RightSingleQuotationMark:

            * (int *) pValue = pCharacter->rightSingleQuotationMark;

            return (TRUE);

        case motelCharacterMember_Prime:

            * (int *) pValue = pCharacter->prime;

            return (TRUE);

        case motelCharacterMember_ReversedPrime:

            * (int *) pValue = pCharacter->reversedPrime;

            return (TRUE);

        case motelCharacterMember_DoublePrime:

            * (int *) pValue = pCharacter->doublePrime;

            return (TRUE);

        case motelCharacterMember_ReversedDoublePrime:

            * (int *) pValue = pCharacter->reversedDoublePrime;

            return (TRUE);

        case motelCharacterMember_TriplePrime:

            * (int *) pValue = pCharacter->triplePrime;

            return (TRUE);

        case motelCharacterMember_ReversedTriplePrime:

            * (int *) pValue = pCharacter->reversedTriplePrime;

            return (TRUE);

        case motelCharacterMember_InvertedQuestionMark:

            * (int *) pValue = pCharacter->invertedQuestionMark;

            return (TRUE);

        case motelCharacterMember_QuestionMark:

            * (int *) pValue = pCharacter->questionMark;

            return (TRUE);

        case motelCharacterMember_InvertedExclamationMark:

            * (int *) pValue = pCharacter->invertedExclamationMark;

            return (TRUE);

        case motelCharacterMember_ExclamationMark:

            * (int *) pValue = pCharacter->exclamationMark;

            return (TRUE);

        case motelCharacterMember_DoubleExclamationMark:

            * (int *) pValue = pCharacter->doubleExclamationMark;

            return (TRUE);

        case motelCharacterMember_FullStop:

            * (int *) pValue = pCharacter->fullStop;

            return (TRUE);

        case motelCharacterMember_Comma:

            * (int *) pValue = pCharacter->comma;

            return (TRUE);

        case motelCharacterMember_Colon:

            * (int *) pValue = pCharacter->colon;

            return (TRUE);

        case motelCharacterMember_Semicolon:

            * (int *) pValue = pCharacter->semicolon;

            return (TRUE);

        case motelCharacterMember_ReversedSemicolon:

            * (int *) pValue = pCharacter->reversedSemicolon;

            return (TRUE);

        case motelCharacterMember_Apostrophe:

            * (int *) pValue = pCharacter->apostrophe;

            return (TRUE);

        case motelCharacterMember_HyphenMinus:

            * (int *) pValue = pCharacter->hyphenMinus;

            return (TRUE);

        case motelCharacterMember_Solidus:

            * (int *) pValue = pCharacter->solidus;

            return (TRUE);

        case motelCharacterMember_RevereseSolidus:

            * (int *) pValue = pCharacter->revereseSolidus;

            return (TRUE);

        case motelCharacterMember_FractionSlash:

            * (int *) pValue = pCharacter->fractionSlash;

            return (TRUE);

        case motelCharacterMember_Caret:

            * (int *) pValue = pCharacter->caret;

            return (TRUE);

        case motelCharacterMember_MiddleDot:

            * (int *) pValue = pCharacter->middleDot;

            return (TRUE);

        case motelCharacterMember_HorizontalEllipsis:

            * (int *) pValue = pCharacter->horizontalEllipsis;

            return (TRUE);

        case motelCharacterMember_PlusSign:

            * (int *) pValue = pCharacter->plusSign;

            return (TRUE);

        case motelCharacterMember_MinusSign:

            * (int *) pValue = pCharacter->minusSign;

            return (TRUE);

        case motelCharacterMember_MultiplicationSign:

            * (int *) pValue = pCharacter->multiplicationSign;

            return (TRUE);

        case motelCharacterMember_DivisionSign:

            * (int *) pValue = pCharacter->divisionSign;

            return (TRUE);

        case motelCharacterMember_SquareRoot:

            * (int *) pValue = pCharacter->squareRoot;

            return (TRUE);

        case motelCharacterMember_EqualsSign:

            * (int *) pValue = pCharacter->equalsSign;

            return (TRUE);

        case motelCharacterMember_LessThanSign:

            * (int *) pValue = pCharacter->lessThanSign;

            return (TRUE);

        case motelCharacterMember_LessThanOrEqualTo:

            * (int *) pValue = pCharacter->lessThanOrEqualTo;

            return (TRUE);

        case motelCharacterMember_GreaterThanSign:

            * (int *) pValue = pCharacter->greaterThanSign;

            return (TRUE);

        case motelCharacterMember_GreaterThanOrEqualTo:

            * (int *) pValue = pCharacter->greaterThanOrEqualTo;

            return (TRUE);

        case motelCharacterMember_NumberSign:

            * (int *) pValue = pCharacter->numberSign;

            return (TRUE);

        case motelCharacterMember_DollarSign:

            * (int *) pValue = pCharacter->dollarSign;

            return (TRUE);

        case motelCharacterMember_PercentSign:

            * (int *) pValue = pCharacter->percentSign;

            return (TRUE);

        case motelCharacterMember_Ampersand:

            * (int *) pValue = pCharacter->ampersand;

            return (TRUE);

        case motelCharacterMember_Asterisk:

            * (int *) pValue = pCharacter->asterisk;

            return (TRUE);

        case motelCharacterMember_CommercialAt:

            * (int *) pValue = pCharacter->commercialAt;

            return (TRUE);

        case motelCharacterMember_VerticalLine:

            * (int *) pValue = pCharacter->verticalLine;

            return (TRUE);

        case motelCharacterMember_DoubleVerticalLine:

            * (int *) pValue = pCharacter->doubleVerticalLine;

            return (TRUE);

        case motelCharacterMember_BrokenBar:

            * (int *) pValue = pCharacter->brokenBar;

            return (TRUE);

        case motelCharacterMember_Tilde:
                
            * (int *) pValue = pCharacter->tilde;

            return (TRUE);

        case motelCharacterMember_FigureDash:
                
            * (int *) pValue = pCharacter->figureDash;

            return (TRUE);

        case motelCharacterMember_HorizontalBar:
                
            * (int *) pValue = pCharacter->horizontalBar;

            return (TRUE);

        case motelCharacterMember_LowLine:

            * (int *) pValue = pCharacter->lowLine;

            return (TRUE);

        case motelCharacterMember_DoubleLowLine:

            * (int *) pValue = pCharacter->doubleLowLine;

            return (TRUE);

        case motelCharacterMember_DashedLowLine:

            * (int *) pValue = pCharacter->dashedLowLine;

            return (TRUE);

        case motelCharacterMember_CentrelineLowLine:

            * (int *) pValue = pCharacter->centrelineLowLine;

            return (TRUE);

        case motelCharacterMember_WavyLowLine:

            * (int *) pValue = pCharacter->wavyLowLine;

            return (TRUE);

        case motelCharacterMember_Overline:

            * (int *) pValue = pCharacter->overline;

            return (TRUE);

        case motelCharacterMember_DashedOverline:

            * (int *) pValue = pCharacter->dashedOverline;

            return (TRUE);

        case motelCharacterMember_CentrelineOverline:

            * (int *) pValue = pCharacter->centrelineOverline;

            return (TRUE);

        case motelCharacterMember_WavyOverline:

            * (int *) pValue = pCharacter->wavyOverline;

            return (TRUE);

        case motelCharacterMember_DoubleWavyOverline:

            * (int *) pValue = pCharacter->doubleWavyOverline;

            return (TRUE);

        case motelCharacterMember_AcuteAccent:

            * (int *) pValue = pCharacter->acuteAccent;

            return (TRUE);

        case motelCharacterMember_DoubleAcuteAccent:

            * (int *) pValue = pCharacter->doubleAcuteAccent;

            return (TRUE);

        case motelCharacterMember_GraveAccent:

            * (int *) pValue = pCharacter->graveAccent;

            return (TRUE);

        case motelCharacterMember_CircumflexAccent:

            * (int *) pValue = pCharacter->circumflexAccent;

            return (TRUE);

        case motelCharacterMember_Caron:

            * (int *) pValue = pCharacter->caron;

            return (TRUE);

        case motelCharacterMember_Breve:

            * (int *) pValue = pCharacter->breve;

            return (TRUE);

        case motelCharacterMember_Diaresis:

            * (int *) pValue = pCharacter->diaresis;

            return (TRUE);

        case motelCharacterMember_Ogonek:

            * (int *) pValue = pCharacter->ogonek;

            return (TRUE);

        case motelCharacterMember_Macron:

            * (int *) pValue = pCharacter->macron;

            return (TRUE);

        case motelCharacterMember_SmallTilde:

            * (int *) pValue = pCharacter->smallTilde;

            return (TRUE);

        case motelCharacterMember_Cedilla:

            * (int *) pValue = pCharacter->cedilla;

            return (TRUE);

        case motelCharacterMember_RingAbove:

            * (int *) pValue = pCharacter->ringAbove;

            return (TRUE);

        case motelCharacterMember_DotAbove:

            * (int *) pValue = pCharacter->dotAbove;

            return (TRUE);

        case motelCharacterMember_OghamFeatherMark:

            * (int *) pValue = pCharacter->oghamFeatherMark;

            return (TRUE);

        case motelCharacterMember_OghamReversedFeatherMark:

            * (int *) pValue = pCharacter->oghamReversedFeatherMark;

            return (TRUE);

        case motelCharacterMember_Space:

            * (int *) pValue = pCharacter->space;

            return (TRUE);

        case motelCharacterMember_Backspace:

            * (int *) pValue = pCharacter->backspace;

            return (TRUE);

        case motelCharacterMember_CharacterTabulation:

            * (int *) pValue = pCharacter->characterTabulation;

            return (TRUE);

        case motelCharacterMember_CarriageReturn:

            * (int *) pValue = pCharacter->carriageReturn;

            return (TRUE);

        case motelCharacterMember_LineFeed:

            * (int *) pValue = pCharacter->lineFeed;

            return (TRUE);

        case motelCharacterMember_NextLine:

            * (int *) pValue = pCharacter->nextLine;

            return (TRUE);

        case motelCharacterMember_LineSeparator:

            * (int *) pValue = pCharacter->lineSeparator;

            return (TRUE);

        case motelCharacterMember_ParagraphSeparator:

            * (int *) pValue = pCharacter->paragraphSeparator;

            return (TRUE);

        case motelCharacterMember_LineTabulation:

            * (int *) pValue = pCharacter->lineTabulation;

            return (TRUE);

        case motelCharacterMember_FormFeed:

            * (int *) pValue = pCharacter->formFeed;

            return (TRUE);
	}

	pCharacter->result = motelResult_InvalidMember;

	return (FALSE);
}
