// void Parser::fillTables() {
//     _actionTable.add(153, $default, REDUCE(0));
//     _actionTable.add(152, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(152, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(152, MINUS, SHIFT(0));
//     _actionTable.add(152, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(152, STAR, SHIFT(0));
//     _actionTable.add(152, OPEN_CURLY, SHIFT(0));
//     _actionTable.add(152, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(152, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(152, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(152, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(152, IDENTIFIER, SHIFT(0));
//     _actionTable.add(152, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(152, BANG, SHIFT(0));
//     _actionTable.add(152, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(152, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(152, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(151, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(150, $default, REDUCE(0));
//     _actionTable.add(149, $default, REDUCE(0));
//     _actionTable.add(148, $default, REDUCE(0));
//     _actionTable.add(147, STAR, SHIFT(0));
//     _actionTable.add(147, $default, REDUCE(0));
//     _actionTable.add(147, IDENTIFIER, SHIFT(0));
//     _actionTable.add(146, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(146, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(146, MINUS, SHIFT(0));
//     _actionTable.add(146, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(146, STAR, SHIFT(0));
//     _actionTable.add(146, OPEN_CURLY, SHIFT(0));
//     _actionTable.add(146, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(146, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(146, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(146, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(146, IDENTIFIER, SHIFT(0));
//     _actionTable.add(146, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(146, BANG, SHIFT(0));
//     _actionTable.add(146, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(146, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(146, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(145, CLOSED_CURLY, SHIFT(0));
//     _actionTable.add(144, $default, REDUCE(0));
//     _actionTable.add(143, SEMICOLON, SHIFT(0));
//     _actionTable.add(142, $default, REDUCE(0));
//     _actionTable.add(141, $default, REDUCE(0));
//     _actionTable.add(141, KEYWORD_ELSE, SHIFT(0));
//     _actionTable.add(140, $default, REDUCE(0));
//     _actionTable.add(139, $default, REDUCE(0));
//     _actionTable.add(139, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(139, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(139, MINUS, SHIFT(0));
//     _actionTable.add(139, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(139, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(139, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(139, IDENTIFIER, SHIFT(0));
//     _actionTable.add(139, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(139, STAR, SHIFT(0));
//     _actionTable.add(139, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(139, BANG, SHIFT(0));
//     _actionTable.add(139, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(139, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(139, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(139, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(138, $default, REDUCE(0));
//     _actionTable.add(138, COMMA, SHIFT(0));
//     _actionTable.add(137, $default, REDUCE(0));
//     _actionTable.add(136, $default, REDUCE(0));
//     _actionTable.add(135, $default, REDUCE(0));
//     _actionTable.add(134, $default, REDUCE(0));
//     _actionTable.add(133, $default, REDUCE(0));
//     _actionTable.add(133, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(133, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(133, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(133, IDENTIFIER, SHIFT(0));
//     _actionTable.add(133, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(133, MINUS, SHIFT(0));
//     _actionTable.add(133, BANG, SHIFT(0));
//     _actionTable.add(132, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(132, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(132, MINUS, SHIFT(0));
//     _actionTable.add(132, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(132, STAR, SHIFT(0));
//     _actionTable.add(132, OPEN_CURLY, SHIFT(0));
//     _actionTable.add(132, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(132, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(132, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(132, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(132, IDENTIFIER, SHIFT(0));
//     _actionTable.add(132, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(132, BANG, SHIFT(0));
//     _actionTable.add(132, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(132, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(132, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(131, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(131, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(131, MINUS, SHIFT(0));
//     _actionTable.add(131, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(131, STAR, SHIFT(0));
//     _actionTable.add(131, OPEN_CURLY, SHIFT(0));
//     _actionTable.add(131, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(131, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(131, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(131, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(131, IDENTIFIER, SHIFT(0));
//     _actionTable.add(131, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(131, BANG, SHIFT(0));
//     _actionTable.add(131, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(131, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(131, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(130, $default, REDUCE(0));
//     _actionTable.add(129, $default, REDUCE(0));
//     _actionTable.add(128, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(128, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(128, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(128, IDENTIFIER, SHIFT(0));
//     _actionTable.add(128, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(128, MINUS, SHIFT(0));
//     _actionTable.add(128, BANG, SHIFT(0));
//     _actionTable.add(127, $default, REDUCE(0));
//     _actionTable.add(126, $default, REDUCE(0));
//     _actionTable.add(126, STAR, SHIFT(0));
//     _actionTable.add(126, AMPERSAND_AMPERSAND, SHIFT(0));
//     _actionTable.add(126, SLASH, SHIFT(0));
//     _actionTable.add(126, AMPERSAND, SHIFT(0));
//     _actionTable.add(125, $default, REDUCE(0));
//     _actionTable.add(125, PIPE_PIPE, SHIFT(0));
//     _actionTable.add(125, MINUS, SHIFT(0));
//     _actionTable.add(125, PLUS, SHIFT(0));
//     _actionTable.add(125, PIPE, SHIFT(0));
//     _actionTable.add(125, CARET, SHIFT(0));
//     _actionTable.add(124, $default, REDUCE(0));
//     _actionTable.add(124, BANG_EQUALS, SHIFT(0));
//     _actionTable.add(124, EQUALS_EQUALS, SHIFT(0));
//     _actionTable.add(124, LESS_THAN, SHIFT(0));
//     _actionTable.add(124, GREATER_THAN, SHIFT(0));
//     _actionTable.add(124, LESS_THAN_EQUALS, SHIFT(0));
//     _actionTable.add(124, GREATER_THAN_EQUALS, SHIFT(0));
//     _actionTable.add(123, $default, REDUCE(0));
//     _actionTable.add(122, $default, REDUCE(0));
//     _actionTable.add(121, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(121, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(121, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(121, IDENTIFIER, SHIFT(0));
//     _actionTable.add(121, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(121, MINUS, SHIFT(0));
//     _actionTable.add(121, BANG, SHIFT(0));
//     _actionTable.add(120, $default, REDUCE(0));
//     _actionTable.add(119, SEMICOLON, SHIFT(0));
//     _actionTable.add(118, $default, REDUCE(0));
//     _actionTable.add(117, $default, REDUCE(0));
//     _actionTable.add(116, $default, REDUCE(0));
//     _actionTable.add(116, OPEN_BRACKET, SHIFT(0));
//     _actionTable.add(115, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(114, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(113, $default, REDUCE(0));
//     _actionTable.add(112, CLOSED_BRACKET, SHIFT(0));
//     _actionTable.add(111, $default, REDUCE(0));
//     _actionTable.add(111, COMMA, SHIFT(0));
//     _actionTable.add(110, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(109, IDENTIFIER, SHIFT(0));
//     _actionTable.add(109, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(109, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(109, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(109, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(108, $default, REDUCE(0));
//     _actionTable.add(107, $default, REDUCE(0));
//     _actionTable.add(106, $default, REDUCE(0));
//     _actionTable.add(105, $default, REDUCE(0));
//     _actionTable.add(104, $default, REDUCE(0));
//     _actionTable.add(103, IDENTIFIER, SHIFT(0));
//     _actionTable.add(103, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(103, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(103, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(103, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(102, $default, REDUCE(0));
//     _actionTable.add(101, $default, REDUCE(0));
//     _actionTable.add(100, $default, REDUCE(0));
//     _actionTable.add(99, $default, REDUCE(0));
//     _actionTable.add(98, $default, REDUCE(0));
//     _actionTable.add(97, $default, REDUCE(0));
//     _actionTable.add(96, $default, REDUCE(0));
//     _actionTable.add(45, $default, REDUCE(0));
//     _actionTable.add(45, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(45, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(45, MINUS, SHIFT(0));
//     _actionTable.add(45, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(45, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(45, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(45, IDENTIFIER, SHIFT(0));
//     _actionTable.add(45, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(45, STAR, SHIFT(0));
//     _actionTable.add(45, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(45, BANG, SHIFT(0));
//     _actionTable.add(45, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(45, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(45, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(45, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(44, CLOSED_CURLY, SHIFT(0));
//     _actionTable.add(43, IDENTIFIER, SHIFT(0));
//     _actionTable.add(42, $default, REDUCE(0));
//     _actionTable.add(41, $default, REDUCE(0));
//     _actionTable.add(40, $default, REDUCE(0));
//     _actionTable.add(39, $default, REDUCE(0));
//     _actionTable.add(38, $default, REDUCE(0));
//     _actionTable.add(37, $default, REDUCE(0));
//     _actionTable.add(37, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(37, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(37, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(37, IDENTIFIER, SHIFT(0));
//     _actionTable.add(37, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(37, MINUS, SHIFT(0));
//     _actionTable.add(37, BANG, SHIFT(0));
//     _actionTable.add(36, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(35, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(34, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(33, IDENTIFIER, SHIFT(0));
//     _actionTable.add(32, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(32, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(32, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(32, IDENTIFIER, SHIFT(0));
//     _actionTable.add(32, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(32, MINUS, SHIFT(0));
//     _actionTable.add(32, BANG, SHIFT(0));
//     _actionTable.add(31, $default, REDUCE(0));
//     _actionTable.add(31, TILDE_EQUALS, REDUCE(0));
//     _actionTable.add(31, PLUS_EQUALS, REDUCE(0));
//     _actionTable.add(31, SLASH_EQUALS, REDUCE(0));
//     _actionTable.add(31, EQUALS, REDUCE(0));
//     _actionTable.add(31, OPEN_BRACKET, SHIFT(0));
//     _actionTable.add(31, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(31, STAR_EQUALS, REDUCE(0));
//     _actionTable.add(31, MINUS_EQUALS, REDUCE(0));
//     _actionTable.add(31, AMPERSAND_EQUALS, REDUCE(0));
//     _actionTable.add(31, PIPE_EQUALS, REDUCE(0));
//     _actionTable.add(31, CARET_EQUALS, REDUCE(0));
//     _actionTable.add(30, $default, REDUCE(0));
//     _actionTable.add(29, $default, REDUCE(0));
//     _actionTable.add(29, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(29, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(29, MINUS, SHIFT(0));
//     _actionTable.add(29, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(29, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(29, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(29, IDENTIFIER, SHIFT(0));
//     _actionTable.add(29, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(29, STAR, SHIFT(0));
//     _actionTable.add(29, KEYWORD_IF, SHIFT(0));
//     _actionTable.add(29, BANG, SHIFT(0));
//     _actionTable.add(29, KEYWORD_WHILE, SHIFT(0));
//     _actionTable.add(29, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(29, KEYWORD_FOR, SHIFT(0));
//     _actionTable.add(29, KEYWORD_RET, SHIFT(0));
//     _actionTable.add(28, STAR, SHIFT(0));
//     _actionTable.add(28, $default, REDUCE(0));
//     _actionTable.add(28, OPEN_BRACKET, SHIFT(0));
//     _actionTable.add(27, $default, REDUCE(0));
//     _actionTable.add(26, OPEN_CURLY, SHIFT(0));
//     _actionTable.add(25, $default, REDUCE(0));
//     _actionTable.add(24, CLOSED_BRACKET, SHIFT(0));
//     _actionTable.add(23, $default, REDUCE(0));
//     _actionTable.add(23, COMMA, SHIFT(0));
//     _actionTable.add(22, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(22, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(22, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(9, $default, REDUCE(0));
//     _actionTable.add(8, $default, REDUCE(0));
//     _actionTable.add(7, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(7, $default, REDUCE(0));
//     _actionTable.add(7, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(7, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(6, $default, REDUCE(0));
//     _actionTable.add(5, $default, ACCEPT);
//     _actionTable.add(5, 0, ACCEPT);
//     _actionTable.add(4, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(0, $default, REDUCE(0));
//     _actionTable.add(0, KEYWORD_FN, SHIFT(0));
//     _actionTable.add(0, 0, ACCEPT);
//     _actionTable.add(1, IDENTIFIER, SHIFT(0));
//     _actionTable.add(2, $end, SHIFT(0));
//     _actionTable.add(2, 0, ACCEPT);
//     _actionTable.add(3, $default, REDUCE(0));
//     _actionTable.add(3, KEYWORD_FN, SHIFT(0));
//     _actionTable.add(10, $default, REDUCE(0));
//     _actionTable.add(11, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(12, $default, REDUCE(0));
//     _actionTable.add(12, COMMA, SHIFT(0));
//     _actionTable.add(13, IDENTIFIER, SHIFT(0));
//     _actionTable.add(14, STAR, SHIFT(0));
//     _actionTable.add(14, $default, REDUCE(0));
//     _actionTable.add(14, OPEN_BRACKET, SHIFT(0));
//     _actionTable.add(15, RIGHT_ARROW, SHIFT(0));
//     _actionTable.add(16, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(16, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(16, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(17, $default, REDUCE(0));
//     _actionTable.add(18, $default, REDUCE(0));
//     _actionTable.add(19, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(20, STAR, SHIFT(0));
//     _actionTable.add(20, $default, REDUCE(0));
//     _actionTable.add(20, OPEN_BRACKET, SHIFT(0));
//     _actionTable.add(21, $default, REDUCE(0));
//     _actionTable.add(46, $default, REDUCE(0));
//     _actionTable.add(47, SEMICOLON, SHIFT(0));
//     _actionTable.add(48, $default, REDUCE(0));
//     _actionTable.add(49, SEMICOLON, SHIFT(0));
//     _actionTable.add(50, TILDE_EQUALS, SHIFT(0));
//     _actionTable.add(50, CARET_EQUALS, SHIFT(0));
//     _actionTable.add(50, PIPE_EQUALS, SHIFT(0));
//     _actionTable.add(50, AMPERSAND_EQUALS, SHIFT(0));
//     _actionTable.add(50, STAR_EQUALS, SHIFT(0));
//     _actionTable.add(50, EQUALS, SHIFT(0));
//     _actionTable.add(50, PLUS_EQUALS, SHIFT(0));
//     _actionTable.add(50, MINUS_EQUALS, SHIFT(0));
//     _actionTable.add(50, SLASH_EQUALS, SHIFT(0));
//     _actionTable.add(51, $default, REDUCE(0));
//     _actionTable.add(52, $default, REDUCE(0));
//     _actionTable.add(53, $default, REDUCE(0));
//     _actionTable.add(54, $default, REDUCE(0));
//     _actionTable.add(55, $default, REDUCE(0));
//     _actionTable.add(56, SEMICOLON, SHIFT(0));
//     _actionTable.add(57, $default, REDUCE(0));
//     _actionTable.add(57, BANG_EQUALS, SHIFT(0));
//     _actionTable.add(57, EQUALS_EQUALS, SHIFT(0));
//     _actionTable.add(57, LESS_THAN, SHIFT(0));
//     _actionTable.add(57, GREATER_THAN, SHIFT(0));
//     _actionTable.add(57, LESS_THAN_EQUALS, SHIFT(0));
//     _actionTable.add(57, GREATER_THAN_EQUALS, SHIFT(0));
//     _actionTable.add(58, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(58, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(58, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(58, IDENTIFIER, SHIFT(0));
//     _actionTable.add(58, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(58, MINUS, SHIFT(0));
//     _actionTable.add(58, BANG, SHIFT(0));
//     _actionTable.add(59, $default, REDUCE(0));
//     _actionTable.add(60, $default, REDUCE(0));
//     _actionTable.add(60, PIPE_PIPE, SHIFT(0));
//     _actionTable.add(60, MINUS, SHIFT(0));
//     _actionTable.add(60, PLUS, SHIFT(0));
//     _actionTable.add(60, PIPE, SHIFT(0));
//     _actionTable.add(60, CARET, SHIFT(0));
//     _actionTable.add(61, $default, REDUCE(0));
//     _actionTable.add(61, STAR, SHIFT(0));
//     _actionTable.add(61, AMPERSAND_AMPERSAND, SHIFT(0));
//     _actionTable.add(61, SLASH, SHIFT(0));
//     _actionTable.add(61, AMPERSAND, SHIFT(0));
//     _actionTable.add(62, $default, REDUCE(0));
//     _actionTable.add(62, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(62, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(62, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(62, IDENTIFIER, SHIFT(0));
//     _actionTable.add(62, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(62, MINUS, SHIFT(0));
//     _actionTable.add(62, BANG, SHIFT(0));
//     _actionTable.add(63, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(63, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(63, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(63, IDENTIFIER, SHIFT(0));
//     _actionTable.add(63, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(63, MINUS, SHIFT(0));
//     _actionTable.add(63, BANG, SHIFT(0));
//     _actionTable.add(64, $default, REDUCE(0));
//     _actionTable.add(64, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(65, CLOSED_PAREN, SHIFT(0));
//     _actionTable.add(66, $default, REDUCE(0));
//     _actionTable.add(67, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(67, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(67, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(67, IDENTIFIER, SHIFT(0));
//     _actionTable.add(67, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(67, MINUS, SHIFT(0));
//     _actionTable.add(67, BANG, SHIFT(0));
//     _actionTable.add(68, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(68, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(68, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(68, IDENTIFIER, SHIFT(0));
//     _actionTable.add(68, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(68, MINUS, SHIFT(0));
//     _actionTable.add(68, BANG, SHIFT(0));
//     _actionTable.add(69, $default, REDUCE(0));
//     _actionTable.add(69, IDENTIFIER, SHIFT(0));
//     _actionTable.add(69, KEYWORD_INT, SHIFT(0));
//     _actionTable.add(69, KEYWORD_FLOAT, SHIFT(0));
//     _actionTable.add(69, STAR, SHIFT(0));
//     _actionTable.add(69, KEYWORD_CHAR, SHIFT(0));
//     _actionTable.add(70, SEMICOLON, SHIFT(0));
//     _actionTable.add(71, $default, REDUCE(0));
//     _actionTable.add(72, $default, REDUCE(0));
//     _actionTable.add(72, EQUALS, SHIFT(0));
//     _actionTable.add(73, $default, REDUCE(0));
//     _actionTable.add(74, $default, REDUCE(0));
//     _actionTable.add(75, $default, REDUCE(0));
//     _actionTable.add(76, $default, REDUCE(0));
//     _actionTable.add(77, $default, REDUCE(0));
//     _actionTable.add(78, $default, REDUCE(0));
//     _actionTable.add(79, $default, REDUCE(0));
//     _actionTable.add(80, $default, REDUCE(0));
//     _actionTable.add(81, $default, REDUCE(0));
//     _actionTable.add(82, $default, REDUCE(0));
//     _actionTable.add(83, $default, REDUCE(0));
//     _actionTable.add(84, $default, REDUCE(0));
//     _actionTable.add(85, $default, REDUCE(0));
//     _actionTable.add(86, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(86, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(86, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(86, IDENTIFIER, SHIFT(0));
//     _actionTable.add(86, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(86, MINUS, SHIFT(0));
//     _actionTable.add(86, BANG, SHIFT(0));
//     _actionTable.add(87, $default, REDUCE(0));
//     _actionTable.add(88, $default, REDUCE(0));
//     _actionTable.add(89, $default, REDUCE(0));
//     _actionTable.add(90, $default, REDUCE(0));
//     _actionTable.add(91, $default, REDUCE(0));
//     _actionTable.add(92, $default, REDUCE(0));
//     _actionTable.add(93, $default, REDUCE(0));
//     _actionTable.add(94, $default, REDUCE(0));
//     _actionTable.add(95, FLOAT_LITERAL, SHIFT(0));
//     _actionTable.add(95, CHAR_LITERAL, SHIFT(0));
//     _actionTable.add(95, INTEGER_LITERAL, SHIFT(0));
//     _actionTable.add(95, IDENTIFIER, SHIFT(0));
//     _actionTable.add(95, OPEN_PAREN, SHIFT(0));
//     _actionTable.add(95, MINUS, SHIFT(0));
//     _actionTable.add(95, BANG, SHIFT(0));
//     _gotoTable.add(147, ForUpdate, 0);
//     _gotoTable.add(147, AssignTarget, 0);
//     _gotoTable.add(147, AssignExpr, 0);
//     _gotoTable.add(146, SimpleExpr, 0);
//     _gotoTable.add(146, UnaryOp, 0);
//     _gotoTable.add(146, ExprStmt, 0);
//     _gotoTable.add(146, ReturnStmt, 0);
//     _gotoTable.add(146, ForStmt, 0);
//     _gotoTable.add(146, WhileStmt, 0);
//     _gotoTable.add(146, Body, 0);
//     _gotoTable.add(146, Stmt, 0);
//     _gotoTable.add(146, Term, 0);
//     _gotoTable.add(146, BaseType, 0);
//     _gotoTable.add(146, UnaryExpr, 0);
//     _gotoTable.add(146, AssignExpr, 0);
//     _gotoTable.add(146, Expr, 0);
//     _gotoTable.add(146, VarDeclStmt, 0);
//     _gotoTable.add(146, VarDeclExpr, 0);
//     _gotoTable.add(146, Type, 0);
//     _gotoTable.add(146, AssignStmt, 0);
//     _gotoTable.add(146, Factor, 0);
//     _gotoTable.add(146, IfStmt, 0);
//     _gotoTable.add(146, AssignTarget, 0);
//     _gotoTable.add(138, ExprTail, 0);
//     _gotoTable.add(132, SimpleExpr, 0);
//     _gotoTable.add(132, UnaryOp, 0);
//     _gotoTable.add(132, ExprStmt, 0);
//     _gotoTable.add(132, ReturnStmt, 0);
//     _gotoTable.add(132, ForStmt, 0);
//     _gotoTable.add(132, WhileStmt, 0);
//     _gotoTable.add(132, Body, 0);
//     _gotoTable.add(132, Stmt, 0);
//     _gotoTable.add(132, Term, 0);
//     _gotoTable.add(132, BaseType, 0);
//     _gotoTable.add(132, UnaryExpr, 0);
//     _gotoTable.add(132, AssignExpr, 0);
//     _gotoTable.add(132, Expr, 0);
//     _gotoTable.add(132, VarDeclStmt, 0);
//     _gotoTable.add(132, VarDeclExpr, 0);
//     _gotoTable.add(132, Type, 0);
//     _gotoTable.add(132, AssignStmt, 0);
//     _gotoTable.add(132, Factor, 0);
//     _gotoTable.add(132, IfStmt, 0);
//     _gotoTable.add(132, AssignTarget, 0);
//     _gotoTable.add(128, Factor, 0);
//     _gotoTable.add(128, Term, 0);
//     _gotoTable.add(128, UnaryOp, 0);
//     _gotoTable.add(128, SimpleExpr, 0);
//     _gotoTable.add(128, Expr, 0);
//     _gotoTable.add(128, UnaryExpr, 0);
//     _gotoTable.add(125, AddOp, 0);
//     _gotoTable.add(125, AddOpTail, 0);
//     _gotoTable.add(124, RelOp, 0);
//     _gotoTable.add(124, RelOpTail, 0);
//     _gotoTable.add(121, Factor, 0);
//     _gotoTable.add(121, Term, 0);
//     _gotoTable.add(121, UnaryOp, 0);
//     _gotoTable.add(121, SimpleExpr, 0);
//     _gotoTable.add(121, Expr, 0);
//     _gotoTable.add(121, UnaryExpr, 0);
//     _gotoTable.add(111, ExprTail, 0);
//     _gotoTable.add(103, Factor, 0);
//     _gotoTable.add(103, Term, 0);
//     _gotoTable.add(95, Factor, 0);
//     _gotoTable.add(95, UnaryExpr, 0);
//     _gotoTable.add(95, SimpleExpr, 0);
//     _gotoTable.add(95, UnaryOp, 0);
//     _gotoTable.add(95, Term, 0);
//     _gotoTable.add(133, Factor, 0);
//     _gotoTable.add(133, SimpleExpr, 0);
//     _gotoTable.add(133, ExprOpt, 0);
//     _gotoTable.add(133, Term, 0);
//     _gotoTable.add(133, UnaryOp, 0);
//     _gotoTable.add(133, Expr, 0);
//     _gotoTable.add(133, UnaryExpr, 0);
//     _gotoTable.add(86, Factor, 0);
//     _gotoTable.add(86, Term, 0);
//     _gotoTable.add(86, UnaryOp, 0);
//     _gotoTable.add(86, SimpleExpr, 0);
//     _gotoTable.add(86, Expr, 0);
//     _gotoTable.add(86, UnaryExpr, 0);
//     _gotoTable.add(72, InitOpt, 0);
//     _gotoTable.add(68, Factor, 0);
//     _gotoTable.add(68, Term, 0);
//     _gotoTable.add(68, UnaryOp, 0);
//     _gotoTable.add(68, SimpleExpr, 0);
//     _gotoTable.add(68, Expr, 0);
//     _gotoTable.add(68, UnaryExpr, 0);
//     _gotoTable.add(28, TypeTail, 0);
//     _gotoTable.add(109, Factor, 0);
//     _gotoTable.add(62, Factor, 0);
//     _gotoTable.add(62, SimpleExpr, 0);
//     _gotoTable.add(62, ExprList, 0);
//     _gotoTable.add(62, Term, 0);
//     _gotoTable.add(62, UnaryOp, 0);
//     _gotoTable.add(62, Expr, 0);
//     _gotoTable.add(62, UnaryExpr, 0);
//     _gotoTable.add(69, ForInit, 0);
//     _gotoTable.add(69, AssignTarget, 0);
//     _gotoTable.add(69, Type, 0);
//     _gotoTable.add(69, VarDeclExpr, 0);
//     _gotoTable.add(69, BaseType, 0);
//     _gotoTable.add(69, AssignExpr, 0);
//     _gotoTable.add(22, BaseType, 0);
//     _gotoTable.add(22, Type, 0);
//     _gotoTable.add(139, SimpleExpr, 0);
//     _gotoTable.add(139, UnaryOp, 0);
//     _gotoTable.add(139, ExprStmt, 0);
//     _gotoTable.add(139, ReturnStmt, 0);
//     _gotoTable.add(139, ForStmt, 0);
//     _gotoTable.add(139, WhileStmt, 0);
//     _gotoTable.add(139, Stmt, 0);
//     _gotoTable.add(139, StmtList, 0);
//     _gotoTable.add(139, Term, 0);
//     _gotoTable.add(139, BaseType, 0);
//     _gotoTable.add(139, UnaryExpr, 0);
//     _gotoTable.add(139, AssignExpr, 0);
//     _gotoTable.add(139, Expr, 0);
//     _gotoTable.add(139, VarDeclStmt, 0);
//     _gotoTable.add(139, VarDeclExpr, 0);
//     _gotoTable.add(139, Type, 0);
//     _gotoTable.add(139, AssignStmt, 0);
//     _gotoTable.add(139, Factor, 0);
//     _gotoTable.add(139, IfStmt, 0);
//     _gotoTable.add(139, AssignTarget, 0);
//     _gotoTable.add(45, SimpleExpr, 0);
//     _gotoTable.add(45, UnaryOp, 0);
//     _gotoTable.add(45, ExprStmt, 0);
//     _gotoTable.add(45, ReturnStmt, 0);
//     _gotoTable.add(45, ForStmt, 0);
//     _gotoTable.add(45, WhileStmt, 0);
//     _gotoTable.add(45, Stmt, 0);
//     _gotoTable.add(45, StmtList, 0);
//     _gotoTable.add(45, Term, 0);
//     _gotoTable.add(45, BaseType, 0);
//     _gotoTable.add(45, UnaryExpr, 0);
//     _gotoTable.add(45, AssignExpr, 0);
//     _gotoTable.add(45, Expr, 0);
//     _gotoTable.add(45, VarDeclStmt, 0);
//     _gotoTable.add(45, VarDeclExpr, 0);
//     _gotoTable.add(45, Type, 0);
//     _gotoTable.add(45, AssignStmt, 0);
//     _gotoTable.add(45, Factor, 0);
//     _gotoTable.add(45, IfStmt, 0);
//     _gotoTable.add(45, AssignTarget, 0);
//     _gotoTable.add(0, FunctionDecl, 0);
//     _gotoTable.add(0, Program, 0);
//     _gotoTable.add(23, ParamTail, 0);
//     _gotoTable.add(131, SimpleExpr, 0);
//     _gotoTable.add(131, UnaryOp, 0);
//     _gotoTable.add(131, ExprStmt, 0);
//     _gotoTable.add(131, ReturnStmt, 0);
//     _gotoTable.add(131, ForStmt, 0);
//     _gotoTable.add(131, WhileStmt, 0);
//     _gotoTable.add(131, Body, 0);
//     _gotoTable.add(131, Stmt, 0);
//     _gotoTable.add(131, Term, 0);
//     _gotoTable.add(131, BaseType, 0);
//     _gotoTable.add(131, UnaryExpr, 0);
//     _gotoTable.add(131, AssignExpr, 0);
//     _gotoTable.add(131, Expr, 0);
//     _gotoTable.add(131, VarDeclStmt, 0);
//     _gotoTable.add(131, VarDeclExpr, 0);
//     _gotoTable.add(131, Type, 0);
//     _gotoTable.add(131, AssignStmt, 0);
//     _gotoTable.add(131, Factor, 0);
//     _gotoTable.add(131, IfStmt, 0);
//     _gotoTable.add(131, AssignTarget, 0);
//     _gotoTable.add(37, Factor, 0);
//     _gotoTable.add(37, SimpleExpr, 0);
//     _gotoTable.add(37, ExprOpt, 0);
//     _gotoTable.add(37, Term, 0);
//     _gotoTable.add(37, UnaryOp, 0);
//     _gotoTable.add(37, Expr, 0);
//     _gotoTable.add(37, UnaryExpr, 0);
//     _gotoTable.add(60, AddOp, 0);
//     _gotoTable.add(60, AddOpTail, 0);
//     _gotoTable.add(7, BaseType, 0);
//     _gotoTable.add(7, Type, 0);
//     _gotoTable.add(7, Param, 0);
//     _gotoTable.add(7, ParamList, 0);
//     _gotoTable.add(12, ParamTail, 0);
//     _gotoTable.add(152, SimpleExpr, 0);
//     _gotoTable.add(152, UnaryOp, 0);
//     _gotoTable.add(152, ExprStmt, 0);
//     _gotoTable.add(152, ReturnStmt, 0);
//     _gotoTable.add(152, ForStmt, 0);
//     _gotoTable.add(152, WhileStmt, 0);
//     _gotoTable.add(152, Body, 0);
//     _gotoTable.add(152, Stmt, 0);
//     _gotoTable.add(152, Term, 0);
//     _gotoTable.add(152, BaseType, 0);
//     _gotoTable.add(152, UnaryExpr, 0);
//     _gotoTable.add(152, AssignExpr, 0);
//     _gotoTable.add(152, Expr, 0);
//     _gotoTable.add(152, VarDeclStmt, 0);
//     _gotoTable.add(152, VarDeclExpr, 0);
//     _gotoTable.add(152, Type, 0);
//     _gotoTable.add(152, AssignStmt, 0);
//     _gotoTable.add(152, Factor, 0);
//     _gotoTable.add(152, IfStmt, 0);
//     _gotoTable.add(152, AssignTarget, 0);
//     _gotoTable.add(58, Factor, 0);
//     _gotoTable.add(58, UnaryExpr, 0);
//     _gotoTable.add(58, SimpleExpr, 0);
//     _gotoTable.add(58, UnaryOp, 0);
//     _gotoTable.add(58, Term, 0);
//     _gotoTable.add(29, SimpleExpr, 0);
//     _gotoTable.add(29, UnaryOp, 0);
//     _gotoTable.add(29, ExprStmt, 0);
//     _gotoTable.add(29, ReturnStmt, 0);
//     _gotoTable.add(29, ForStmt, 0);
//     _gotoTable.add(29, WhileStmt, 0);
//     _gotoTable.add(29, Stmt, 0);
//     _gotoTable.add(29, StmtList, 0);
//     _gotoTable.add(29, Term, 0);
//     _gotoTable.add(29, BaseType, 0);
//     _gotoTable.add(29, UnaryExpr, 0);
//     _gotoTable.add(29, AssignExpr, 0);
//     _gotoTable.add(29, Expr, 0);
//     _gotoTable.add(29, VarDeclStmt, 0);
//     _gotoTable.add(29, VarDeclExpr, 0);
//     _gotoTable.add(29, Type, 0);
//     _gotoTable.add(29, AssignStmt, 0);
//     _gotoTable.add(29, Factor, 0);
//     _gotoTable.add(29, IfStmt, 0);
//     _gotoTable.add(29, AssignTarget, 0);
//     _gotoTable.add(126, MulOp, 0);
//     _gotoTable.add(126, MulOpTail, 0);
//     _gotoTable.add(32, Factor, 0);
//     _gotoTable.add(32, Term, 0);
//     _gotoTable.add(32, UnaryOp, 0);
//     _gotoTable.add(32, SimpleExpr, 0);
//     _gotoTable.add(32, Expr, 0);
//     _gotoTable.add(32, UnaryExpr, 0);
//     _gotoTable.add(3, FunctionDecl, 0);
//     _gotoTable.add(3, Program, 0);
//     _gotoTable.add(50, AssignOp, 0);
//     _gotoTable.add(57, RelOp, 0);
//     _gotoTable.add(57, RelOpTail, 0);
//     _gotoTable.add(14, TypeTail, 0);
//     _gotoTable.add(61, MulOp, 0);
//     _gotoTable.add(61, MulOpTail, 0);
//     _gotoTable.add(16, BaseType, 0);
//     _gotoTable.add(16, Type, 0);
//     _gotoTable.add(16, Param, 0);
//     _gotoTable.add(63, Factor, 0);
//     _gotoTable.add(63, Term, 0);
//     _gotoTable.add(63, UnaryOp, 0);
//     _gotoTable.add(63, SimpleExpr, 0);
//     _gotoTable.add(63, Expr, 0);
//     _gotoTable.add(63, UnaryExpr, 0);
//     _gotoTable.add(20, TypeTail, 0);
//     _gotoTable.add(67, Factor, 0);
//     _gotoTable.add(67, Term, 0);
//     _gotoTable.add(67, UnaryOp, 0);
//     _gotoTable.add(67, SimpleExpr, 0);
//     _gotoTable.add(67, Expr, 0);
//     _gotoTable.add(67, UnaryExpr, 0);
// }
