module RosettaJSON.Parse.ParseJSON
    ( parseJSON
    ) where

import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)
import RosettaJSON.Parse.ParseJSONLiteral (parseJSONNull, parseJSONBool)
import RosettaJSON.Parse.ParseJSONNumber (parseJSONNumber)
import RosettaJSON.Parse.ParseJSONString (parseJSONString)
import RosettaJSON.Parse.ParseJSONArray (parseJSONArray)
import RosettaJSON.Parse.ParseJSONObject (parseJSONObject)

parseJSON :: String -> ParseResult
parseJSON s = parseJSONValue s 

parseJSONValue :: String -> ParseResult
parseJSONValue "" = Left EmptyString 
parseJSONValue input@(c : _)
    | c == 'n'              = parseJSONNull input
    | c == 't'              = parseJSONBool input
    | c == 'f'              = parseJSONBool input
    | c == '-' || isDigit c = parseJSONNumber input
    | c == '"'              = parseJSONString input
    | c == '['              = parseJSONArray parseJSONValue input
    | c == '{'              = parseJSONObject parseJSONString parseJSONValue input
    | otherwise             = Left (UnexpectedChar c)
    where
        isDigit :: Char -> Bool
        isDigit x = elem x "0123456789"
