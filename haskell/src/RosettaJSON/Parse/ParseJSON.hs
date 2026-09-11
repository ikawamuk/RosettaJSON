module RosettaJSON.Parse.ParseJSON
    ( parseJSON
    ) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseError (ParseError(..))
import RosettaJSON.Parse.ParseJSONLiteral (parseJSONNull, parseJSONBool)
import RosettaJSON.Parse.ParseJSONNumber (parseJSONNumber)
import RosettaJSON.Parse.ParseJSONString (parseJSONString)

parseJSON :: String -> Either ParseError (String, JSONValue)
parseJSON s = parseJSONValue s 

parseJSONValue :: String -> Either ParseError (String, JSONValue)
parseJSONValue "" = Left EmptyString 
parseJSONValue input@(c : _)
    | c == 'n'              = parseJSONNull input
    | c == 't'              = parseJSONBool input
    | c == 'f'              = parseJSONBool input
    | c == '-' || isDigit c = parseJSONNumber input
    | c == '"'              = parseJSONString input
--    | c == '['              = parseJSONArray input
--    | c == '{'              = parseJSONObject input
    | otherwise             = Left (UnexpectedChar c)
    where
        isDigit :: Char -> Bool
        isDigit x = elem x "0123456789"
