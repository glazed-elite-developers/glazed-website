type developer = {
  key: string,
  name: string,
  skills: array(string),
  description: string,
  shortDescription: string,
  linkedIn: string,
};

type square =
  | TitleSquare(string)
  | MottoSquare(string)
  | SendApplicationSquare
  | DeveloperSquare(string);

module DeveloperComparable =
  Belt.Id.MakeComparable({
    type t = string;
    let cmp = Pervasives.compare;
  });

let developers =
  Belt.Map.fromArray(
    ~id=(module DeveloperComparable),
    [|
      (
        "matias",
        {
          key: "matias",
          name: "Carlos Matias",
          skills: [|"React", "GraphQL", "Gatsby", "Node"|],
          description: "He mainly develops for the web since web apps reach a larger user base and because the use of modern web technologies delivers performant and rich browsing experiences.",
          shortDescription: "Carlos excels in building applications with great user experience and that users can rely on.",
          linkedIn: "https://www.linkedin.com/in/carlosmatias93/",
        },
      ),
      (
        "cristiano",
        {
          key: "cristiano",
          name: "Cristiano Alves",
          skills: [|"iOS", "Android", "IOT"|],
          description: "He is proficient in iOS and Android development and also has experience with hardware and back-end development.",
          shortDescription: "Cristiano is a mobile app developer whose motivation, knowledge and methodical approach yield great apps.",
          linkedIn: "https://www.linkedin.com/in/cristianoftalves/",
        },
      ),
      (
        "filipe",
        {
          key: "filipe",
          name: {j|Filipe Perdigão|j},
          skills: [|"Node", "Javascript", "Rails"|],
          description: "Javascript (both front-end and node) and Rails are his weapons of choice, but he can adapt to any new team or technology and start adding value to any project very quickly.",
          shortDescription: "Filipe is a very fast and productive full-stack web developer.",
          linkedIn: "https://www.linkedin.com/in/filipeperdigaosousa/",
        },
      ),
      (
        "rick",
        {
          key: "rick",
          name: "Ricardo Moutinho",
          skills: [|"Android", "IOT", "Node", "Javascript"|],
          description: "He's been working on Android since 2011 in projects ranging from state of the art R&D prototypes to robust commercial applications. His knowledge of Android's APIs and ecosystem, full stack experience and understanding of the entire development process have consistently delivered valuable products.",
          shortDescription: "Ricardo is an award winning Android developer.",
          linkedIn: "https://www.linkedin.com/in/rmoutinho/",
        },
      ),
      (
        "figo",
        {
          key: "figo",
          name: "Rui Monteiro",
          skills: [|"React", "Elm", "Javascript", "Node", "ECommerce"|],
          description: "He knows the workings and bugs of browsers, has worked with most tech stacks, so if you're working with him, you're sure to get the best maintainability and performance.",
          shortDescription: "Rui is the ultimate expert in all things Web Frontend and JS.",
          linkedIn: "https://www.linkedin.com/in/figomonteiro/",
        },
      ),
      (
        "miguel",
        {
          key: "miguel",
          name: "Miguel Quintas",
          skills: [|"iOS", "Android", "React Native", "React", "Django"|],
          description: "An incredible generalist, he is one of those mythical developers with several years of experience and many apps shipped in iOS, Android, Frontend and Backend development. He has a very positive attitude and a relentless drive.",
          shortDescription: "Miguel is an efficient developer with extensive web and mobile experience.",
          linkedIn: "https://www.linkedin.com/in/miguel-quintas-6b472046/",
        },
      ),
      (
        "joao",
        {
          key: "joao",
          name: {j|João Barbosa|j},
          skills: [|"iOS", "Android", "Django"|],
          description: "He has delivered many projects for millions of users, for both startups and big companies, and he's worked extensively on back-end and API integrations. He has a very calm positive attitude and works well both alone and on teams.",
          shortDescription: {j|João is a passionate iOS and Android developer with a strong attention to detail that has yielded great apps.|j},
          linkedIn: "https://www.linkedin.com/in/jbarbosa1/",
        },
      ),
      (
        "nuno",
        {
          key: "nuno",
          name: "Nuno Silva",
          skills: [|"iOS", "Android", "C++", "Django"|],
          description: "Nuno is a Mobile Engineer that has developed apps on both iOS and Android for millions of users, and managed mobile and front-end teams.",
          shortDescription: "He's a fast learner and a generalist, with a never ending motivation to go through any challenge and ship the product!",
          linkedIn: "https://www.linkedin.com/in/nunompsilva/",
        },
      ),
      (
        "torres",
        {
          key: "torres",
          name: "Pedro Torres",
          skills: [|"Django", "React", "Full stack", "Node"|],
          description: "He has a strong background in Django Backend development, as well as in JavaScript and Frontend development.",
          shortDescription: "Pedro is a talented web software engineer with successful entrepreneurial experience.",
          linkedIn: "https://www.linkedin.com/in/petorres/",
        },
      ),
      (
        "jose",
        {
          key: "jose",
          name: {j|José Magalhães|j},
          skills: [|"AI", "IOT", "Machine Learning", "Backend", "Java", "Elixir", "Javascript"|],
          description: "His drive is to elevate businesses to their max potential. Throughout the years he's been building self-adaptive systems which are capable of learning in any enviroment.",
          shortDescription: {j|José is an extremely methodical developer who loves performance.|j},
          linkedIn: "https://www.linkedin.com/in/jtpam/",
        },
      ),
      (
        "pedro",
        {
          key: "pedro",
          name: "Pedro Campos",
          skills: [|"Javasctipt", "iOS", "Android", "Django", "Node"|],
          description: "He has developed and managed projects for numerous startups, agencies, and Fortune 500 companies in a wide range of mobile and web platforms. Pedro also excels in software architecture and solving challenging problems.",
          shortDescription: "Pedro is an entrepreneur and software engineer with extensive mobile and web development experience.",
          linkedIn: "https://www.linkedin.com/in/pedromelocampos/",
        },
      ),
      (
        "raspa",
        {
          key: "raspa",
          name: "Pedro Santos",
          skills: [|"iOS", "Javascript", "React", "Django", "Node"|],
          description: "He has developed and managed many projects, and is incredibly experienced in all things software. He is also a great puzzle solver, and great at debugging and logic challenges.",
          shortDescription: "Pedro is an iOS and Web Frontend software engineer and Entrepreneur.",
          linkedIn: "https://www.linkedin.com/in/pedrosantos3/",
        },
      ),
      (
        "maria",
        {
          key: "maria",
          name: "Maria Vasquez",
          skills: [|
            "Partnerships",
            "Clients",
            "Office",
            "Culture",
            "Communication",
            "Accounting",
          |],
          description: "She makes sure Glazed has the best environment possible, where every developer keeps improving, sharing, working on the most interesting projects, and making every client and partner happy.",
          shortDescription: "Maria is in charge of most of our communication, partnership and administrative challenges.",
          linkedIn: "https://www.linkedin.com/in/maria-vasquez-3a1a3b17/",
        },
      ),
      (
        "daniela",
        {
          key: "daniela",
          name: "Daniela Dias",
          skills: [|"iOS", "React Native", "React", "Angular"|],
          description: "She excels at prioritising tasks, setting goals, and simplifying seemingly overly complicated matters to deliver high-quality and exceptional products.",
          shortDescription: "Daniela is an experienced iOS and web frontend developer passionate about user experience.",
          linkedIn: "https://www.linkedin.com/in/danielafpdias/",
        },
      ),
      (
        "batista",
        {
          key: "batista",
          name: "Rui Baptista",
          skills: [|"Java", "C#", "Python", "Javascript", "TypeScript"|],
          description: "He has vast expertise in eCommerce, grocery retailers, ticketing platforms and worked on projects for notable brands such as Coca-Cola, Continente, Unicer.",
          shortDescription: "Rui is a professional software developer with eight years of experience in backend services and hybrid mobile applications.",
          linkedIn: "https://www.linkedin.com/in/rui-b-32a79aa7/",
        },
      ),
      (
        "fox",
        {
          key: "fox",
          name: {j|Ricardo Reis|j},
          skills: [|"Strategy", "Business development", "Project Coordination"|],
          description: "Armed with two decades of culinary expertise, he knows the recipe for success lies in the strength of the team. Now, he's using his skills to cook up sales strategies and market solutions that leave our clients hungry for more.",
          shortDescription: {j|From chef to sales strategist, Ricardo's passion for optimizing performance in the kitchen has translated seamlessly into the tech world.|j},
          linkedIn: "https://www.linkedin.com/in/ricardo-reis-exna/",
        },
      ),
    |],
  );

let squares = [|
  TitleSquare("// team"),
  DeveloperSquare("matias"),
  DeveloperSquare("cristiano"),
  DeveloperSquare("filipe"),
  MottoSquare("Great developers build great code"),
  DeveloperSquare("rick"),
  DeveloperSquare("figo"),
  DeveloperSquare("miguel"),
  DeveloperSquare("joao"),
  DeveloperSquare("daniela"),
  DeveloperSquare("nuno"),
  MottoSquare("Great developers love their work"),
  SendApplicationSquare,
  DeveloperSquare("torres"),
  DeveloperSquare("jose"),
  DeveloperSquare("pedro"),
  DeveloperSquare("raspa"),
  DeveloperSquare("maria"),
  DeveloperSquare("batista"),
  DeveloperSquare("fox"),
|];
