

#ifndef CONFIG_PARSER_HPP
# define CONFIG_PARSER_HPP

# include <fstream>
# include <vector>

class Token;

void	parse(std::ifstream	&file);
void	parseBlock(Token &token);
void	parseDirective(Token &token);
void	handleDirective(const std::string &name, const std::vector<std::string> &args);
void	handleDirectiveStart(const std::string &name, const std::vector<std::string> &args);
void	handleDirectiveEnd(const std::string &name, const std::vector<std::string> &args);

#endif
