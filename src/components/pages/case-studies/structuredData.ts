export type StructuredData = Record<string, unknown>

const basePublisher: StructuredData = {
  '@type': 'Organization',
  name: 'Glazed Solutions',
  url: 'https://www.glazedsolutions.com',
  logo: {
    '@type': 'ImageObject',
    url: 'https://www.glazedsolutions.com/assets/logo.png',
  },
}

const baseIsPartOf: StructuredData = {
  '@type': 'WebSite',
  name: 'Glazed Solutions',
  url: 'https://www.glazedsolutions.com',
}

export const caseStudyStructuredDataBySlug: Partial<
  Record<string, StructuredData>
> = {
  bostonhospital: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: "Case Study: Boston Children’s Hospital",
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/bostonhospital/',
    image:
      'https://www.glazedsolutions.com/assets/case-studies/bostonhospital.jpg',
    description:
      'Engineering a clinical analytics platform to unify FHIR-based data and improve pediatric care workflows.',
    headline: "Boston Children’s Hospital — Engineering case study",
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  bostonchildrenshospital: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: "Case Study: Boston Children’s Hospital",
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/bostonchildrenshospital/',
    image:
      'https://www.glazedsolutions.com/assets/case-studies/bostonchildrenshospital.jpg',
    description:
      'Engineering a clinical analytics platform to unify FHIR-based data and improve pediatric care workflows.',
    headline: "Boston Children’s Hospital — Engineering case study",
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  lvmh: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: LVMH Conversational Platform',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/lvmh/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/lvmh.jpg',
    description:
      'Developing a multi-brand conversational platform combining NLP, visual search, and CRM integration for luxury retail.',
    headline: 'LVMH Conversational Platform — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  canvas: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Canvas Medical',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/canvas/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/canvas.jpg',
    description:
      'Re-architecting a developer-first EMR platform with unified RCM and FHIR APIs to enable intelligent growth.',
    headline: 'Canvas Medical — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  gopuff: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: GoPuff',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/gopuff/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/gopuff.jpg',
    description:
      'Scaling logistics and delivery systems with cloud-native architecture and modernized infrastructure.',
    headline: 'GoPuff — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  mercadao: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Mercadão',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/mercadao/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/mercadao.jpg',
    description:
      'Optimizing a leading grocery marketplace for speed, scalability, and reliability under heavy demand.',
    headline: 'Mercadão — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  farfetch: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Farfetch',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/farfetch/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/farfetch.jpg',
    description:
      'Integrating a personalized customization engine and SDK to enhance global e-commerce scalability.',
    headline: 'Farfetch — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  fruitful: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Fruitful',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/fruitful/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/fruitful.jpg',
    description:
      'Building a FinTech platform for automated savings and investment products with secure API architecture.',
    headline: 'Fruitful — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  newwork: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: New Work',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/newwork/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/newwork.jpg',
    description:
      'Designing a flexible HR platform integrating analytics, automation, and custom workflow systems.',
    headline: 'New Work — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  vessel: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Vessel',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/vessel/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/vessel.jpg',
    description:
      'Developing a digital health platform that combines diagnostics, user engagement, and personalized recommendations.',
    headline: 'Vessel — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
  pasabi: {
    '@context': 'https://schema.org',
    '@type': ['WebPage', 'CreativeWork'],
    name: 'Case Study: Pasabi',
    publisher: basePublisher,
    url: 'https://www.glazedsolutions.com/case-studies/pasabi/',
    image: 'https://www.glazedsolutions.com/assets/case-studies/pasabi.jpg',
    description:
      'Engineering a scalable AI-driven trust and safety platform with advanced fraud detection capabilities.',
    headline: 'Pasabi — Engineering case study',
    isPartOf: baseIsPartOf,
    inLanguage: 'en',
  },
}

export const caseStudiesCollectionPage: StructuredData = {
  '@context': 'https://schema.org',
  '@type': 'CollectionPage',
  name: 'Case Studies | Glazed Solutions',
  url: 'https://www.glazedsolutions.com/case-studies/',
  description:
    'A curated collection of software engineering case studies by Glazed Solutions — showcasing how we help global brands in FinTech, HealthTech, AI, and Digital Commerce build scalable, high-performance digital products.',
  publisher: {
    '@type': 'Organization',
    name: 'Glazed Solutions',
    url: 'https://www.glazedsolutions.com',
    logo: 'https://www.glazedsolutions.com/assets/logo.png',
  },
  about: [
    'Software Engineering',
    'FinTech Development',
    'HealthTech Systems',
    'AI Platforms',
    'Digital Commerce',
    'Product Scalability',
  ],
}
