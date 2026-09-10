module RosettaJSON.Parse
	( parseJSON ) where

import RosettaJSON.Types (JSONValue(..))

parseJSON :: String -> Either String JSONValue
parseJSON = parseJSONValue

parseJSONValue :: String -> Either String JSONValue
parseJSONValue = parseJSONNull
			 <|> parseJSONTrue
			 <|> parseJSONFalse
			 <|> parseJSONNumber
			 <|> parseJSONString
			 <|> parseJSONArray
			 <|> parseJSONObject
