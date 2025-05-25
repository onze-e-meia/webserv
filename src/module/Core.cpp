

#include <iostream>


// #include "Parser.hpp"
#include "Core.hpp"

#define CORE_NAME(structName, name, nb) \
	static Core::C_CoreSpec	structName(#name, &Core::name##_Handler, nb)

typedef	std::map<std::string, Core::HandlerPointer>	DirectiveMap;
typedef DirectiveMap::const_iterator				DirectiveConst_it;

CORE_NAME(ROOT, root, 1);
CORE_NAME(INDEX, index, 1);
CORE_NAME(AUTO_INDEX, autoindex, 1);
CORE_NAME(ERRO_PAGE, error_page, 16);
CORE_NAME(CLIENT_MAX_BODY, client_max_body_size, 1);
CORE_NAME(METHODS, allow_methods, 8);
static Core::C_CoreSpec EMPTY("empty", NULL, 0);

static Core::C_CoreSpec	CORE_HANDLER[] = {
	ROOT, INDEX, AUTO_INDEX, ERRO_PAGE, CLIENT_MAX_BODY, METHODS
};

static const DirectiveMap	buildMap(void) {
	DirectiveMap	map;
	for (std::size_t i = 0; CORE_HANDLER[i]._handler != NULL; ++i)
		map[CORE_HANDLER[i]._name] = CORE_HANDLER[i]._handler;
	return (map);
}

static const DirectiveMap	CORE_MAP = buildMap();

// =============================================================================
// PROTECTED
// =============================================================================

/* Member Functions */


// =============================================================================
// PUBLIC
// =============================================================================

/* Contsructor */
Core::Core(const Block::Module &block): _blockType(block) {}

/* Destructor */
Core::~Core(void) {}

/* Member Functions */


/* Handlers */
Core::HandlerPointer	Core::selectHandler(C_Str &name) {
	DirectiveConst_it	it = CORE_MAP.find(name);
	DirectiveConst_it	end = CORE_MAP.end();
	if (it == end)
		return (NULL);
	return (it->second);
}

void	Core::root_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, ROOT, outerBlock, args);
	// std::cerr <<
	if (args.at(0).at(0) != '/')
		throw (InvalidType(parser, ROOT._name, outerBlock, args));
}

void	Core::index_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, INDEX, outerBlock, args);
}

void	Core::autoindex_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, AUTO_INDEX, outerBlock, args);
}

void	Core::error_page_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, ERRO_PAGE, outerBlock, args);
}

void	Core::client_max_body_size_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, CLIENT_MAX_BODY, outerBlock, args);
}

void	Core::allow_methods_Handler(C_Parser &parser, C_Str &directive, C_Block &outerBlock, C_VecStr &args) {
	(void)directive; // TODO: Need this var here?
	checkArgs(parser, METHODS, outerBlock, args);
}
