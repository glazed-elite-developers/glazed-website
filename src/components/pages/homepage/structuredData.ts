export type StructuredData = Record<string, unknown>

export const homepageOrganization: StructuredData = {
  '@context': 'https://schema.org',
  '@type': 'Organization',
  name: 'Glazed Solutions',
  url: 'https://www.glazedsolutions.com',
  logo: 'https://www.glazedsolutions.com/assets/logo.png',
  description:
    'Glazed Solutions is a developer-only engineering partner building high-performance software across FinTech, HealthTech, AI, and Digital Commerce.',
  foundingDate: '2014',
  foundingLocation: {
    '@type': 'Place',
    address: {
      '@type': 'PostalAddress',
      addressLocality: 'Porto',
      addressCountry: 'Portugal',
    },
  },
  contactPoint: {
    '@type': 'ContactPoint',
    contactType: 'Business',
    email: 'info@glazedsolutions.com',
  },
  sameAs: [
    'https://www.linkedin.com/company/glazedsolutions',
    'https://x.com/glazedsolutions',
  ],
  department: [
    {
      '@type': 'Organization',
      name: 'About',
      url: 'https://www.glazedsolutions.com/#about',
      description:
        'Glazed Solutions is a senior software engineering company from Porto, Portugal, focused on quality, speed, and scalability.',
    },
    {
      '@type': 'Organization',
      name: 'Team',
      url: 'https://www.glazedsolutions.com/#team',
      description:
        'A small, senior team of software engineers with over 10 years of experience each, delivering secure and scalable products.',
    },
    {
      '@type': 'Organization',
      name: 'Manifesto',
      url: 'https://www.glazedsolutions.com/#manifesto',
      description:
        'We believe in clean code, technical depth, and long-term partnerships that compound.',
    },
  ],
  knowsAbout: [
    'Software Engineering',
    'FinTech Development',
    'HealthTech Systems',
    'AI Platforms',
    'Digital Commerce',
    'Cloud Infrastructure',
    'Product Scalability',
  ],
}
