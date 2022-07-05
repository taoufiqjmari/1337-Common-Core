#include "webserv.hpp"

void setup_config_file(int argc, char **argv, std::string &config_file)
{
	if (argc == 2)
	{
		config_file = argv[1];
		// ./webserv --help || -h
		if (config_file == "--help" || config_file == "-h")
			PRINT("Usage: " << argv[0] << " [configuration file]");
		// ./webserv [configuration file]
		else
		{
			read_config_file(config_file);
			return;
		}
	}
	// ./webserv || ./webserv param1 param2 ...
	else
	{
		PRINT("Usage: " << argv[0] << " [configuration file]");
		PRINT("Usage: " << argv[0] << " --help [-h]");
	}
	exit(EXIT_SUCCESS);
}

void read_config_file(std::string &config_file)
{
	std::ifstream in_stream(config_file.c_str());
	std::string line;

	if (!in_stream)
	{
		PRINT_ERR("Error: Could not open file " << config_file);
		exit(EXIT_FAILURE);
	}
	config_file.clear();
	while (std::getline(in_stream, line))
		config_file += line + "\n";
	in_stream.close();
}

void exit_err(std::string &err)
{
	PRINT_ERR(err);
	exit(EXIT_FAILURE);
}

void signal_pipe(int sig)
{
	(void)sig;
}

int main(int argc, char **argv)
{
	std::string config_file;
	std::vector<Server> servers;

	signal(SIGPIPE, signal_pipe);
	//////////////////////////////////////////////////
	// Initialization
	//////////////////////////////////////////////////
	setup_config_file(argc, argv, config_file);

	//////////////////////////////////////////////////
	// Parsing
	//////////////////////////////////////////////////
	try
	{
		Parser parser(config_file);
		servers = parser.get_servers();
	}
	catch (std::string &err)
	{
		exit_err(err);
	}
	// print_servers(servers);

	//////////////////////////////////////////////////
	// Processing
	//////////////////////////////////////////////////
	{
		looper(servers);
	}
	return EXIT_SUCCESS;
}
